#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Threading/ThreadUtil.hpp"
#include "CUL/Threading/ThreadWrap.hpp"
#include <CUL/Filesystem/DiskScheduler.hpp>

#include "CUL/CULInterface.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/Hardware/DiskInfo.hpp"
#include <CUL/Messaging/MessageSystem.hpp>
#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_iterator.hpp"
#include "IMPORT_hash_library.hpp"

using namespace CUL;
using namespace FS;

static const StringWr g_emptyString;

#if 0  // DEBUG_THIS_FILE, set 0->1 to debug
    #define DEBUG_THIS_FILE 1

    #if defined( CUL_COMPILER_MSVC )
        #pragma optimize( "", off )
    #elif defined( CUL_COMPILER_CLANG )
        #pragma clang optimize off
    #elif defined( CUL_COMPILER_GCC )
        #pragma GCC push_options
        #pragma GCC optimize( "O0" )
    #endif
#endif

IFile::IFile( const StringWr& fPath, CUL::CULInterface* inInterface )
    : p_cullInterface( inInterface )
{
    m_path.createFrom( fPath );
    p_cullInterface->getFS()->getLastModificationTime( m_path, m_lastModificationTime );
    calculateSizeBytes();
}

const Path& IFile::getPath() const
{
    return m_path;
}

const StringWr& IFile::firstLine() const
{
    throw std::logic_error( "Method not implemented" );
    return g_emptyString;
}

const StringWr& IFile::lastLine() const
{
    throw std::logic_error( "Method not implemented" );
    return g_emptyString;
}

const StringWr& IFile::getAsOneString() const
{
    throw std::logic_error( "Method not implemented" );
    return g_emptyString;
}

const char** IFile::getContent() const
{
    throw std::logic_error( "Method not implemented" );
    return nullptr;
}

std::uint32_t IFile::getLinesCount() const
{
    throw std::logic_error( "Method not implemented" );
    return 0u;
}

void IFile::setPath( const StringWr& fPath )
{
    m_path.createFrom( fPath );
    calculateSizeBytes();
}

void IFile::addLine( const StringWr& )
{
    throw std::logic_error( "Method not implemented" );
}

void IFile::saveFile()
{
    throw std::logic_error( "Method not implemented" );
}

void IFile::load( bool /*keepLineEndingCharacter*/, bool /*removeBottomEmptyLines*/ )
{
    throw std::logic_error( "Method not implemented" );
}

void IFile::loadFromString( const StringWr& /*contents*/,
                            bool /*keepLineEndingCharacter = false */ )
{
    throw std::logic_error( "Method not implemented" );
}

void IFile::loadFromStringNoEmptyLines( const StringWr& /*contents*/,
                                        bool /*keepLineEndingCharacter*/ )
{
    throw std::logic_error( "Method not implemented" );
}

bool IFile::exists() const
{
    return getPath().exists();
}

const FileList& IFile::getChildList() const
{
    return m_fileList;
}

void IFile::addChild( IFile* file )
{
    m_fileList.emplace( file );
}

bool IFile::operator==( const IFile& arg ) const
{
    return getPath() == arg.getPath();
}

bool IFile::operator<( const IFile& arg ) const
{
    return getPath() < arg.getPath();
}

bool IFile::operator>( const IFile& arg ) const
{
    return getPath() > arg.getPath();
}

void IFile::getCreationTime( Time& outTime )
{
    outTime = m_creationTime;
}

void IFile::getLastModificationTime( Time& outTime )
{
    if( m_lastModificationTime.getUs() > 0u )
    {
        outTime = m_lastModificationTime;
        return;
    }

    if( p_cullInterface->getFS()->fileExist( m_path ) )
    {
        p_cullInterface->getFS()->getLastModificationTime( m_path,
                                                           m_lastModificationTime );
    }
    outTime = m_lastModificationTime;
}

void IFile::toggleCache( bool enabled )
{
    m_cacheEnabled = enabled;
}

bool IFile::getIsCacheEnabled() const
{
    return m_cacheEnabled;
}

const StringWr& IFile::getMD5()
{
    if( m_md5.empty() )
    {
        calculateMD5();
    }
    return m_md5;
}

const char* IFile::getUtfChar() const
{
    const char* name = __func__;
    Assert::check( false, "NOT IMPLEMENTED: %s", name );
    return nullptr;
}

std::string IFile::getLineUtf( std::int32_t /*inLineNum*/ ) const
{
    const char* name = __func__;
    Assert::check( false, "NOT IMPLEMENTED: %s", name );
    return std::string();
}

std::wstring IFile::getLineW( std::int32_t /*inLineNum*/ ) const
{
    const char* name = __func__;
    Assert::check( false, "NOT IMPLEMENTED: %s", name );
    return std::wstring();
}

void IFile::calculateMD5()
{
    if( getIsBigFile() )
    {
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info,
                                                 "[IFile::calculateMD5] Big file: %s",
                                                 getPath().getPath().getUtfChar() );

        CDiskScheduler::getInstance().executeWhenPossibleWithWait(
            getPath().getPath(),
            [this]()
            {
                calculateBigFileImpl();
            } );
    }
    else
    {
        std::ifstream file( getPath().getPath().getValue(), std::ios::binary );
        file.unsetf( std::ios::skipws );

        const std::uint64_t fileSizeAsNumber = getSizeInBytes();
        std::vector<unsigned char> vec;
        vec.reserve( fileSizeAsNumber );
        vec.insert( vec.begin(),
                    std::istream_iterator<unsigned char>( file ),
                    std::istream_iterator<unsigned char>() );
        if( vec.empty() == false )
        {
            SHA256 sha256;
            m_md5 = sha256( vec.data(), fileSizeAsNumber );
        }

        file.close();
    }
}

void IFile::calculateBigFileImpl()
{
    std::ifstream file( getPath().getPath().getValue(), std::ios::binary );
    if( !file.is_open() )
    {
        return;
    }

    constexpr std::size_t bytesPerRead = 16384u;
    char buffer[bytesPerRead];

    SHA256 sha256;
    const std::uint64_t fileSizeAsNumber = getSizeInBytes();
    std::uint64_t bytesHashed = 0u;

    SBigMD5FileCalc calcinfo;
    calcinfo.Path = getPath();
    calcinfo.Progress = 0.f;

    while( file )
    {
        file.read( buffer, static_cast<std::streamsize>( bytesPerRead ) );
        const std::streamsize bytesRead = file.gcount();
        if( bytesRead <= 0 )
        {
            break;
        }

        sha256.add( buffer, static_cast<std::size_t>( bytesRead ) );
        bytesHashed += static_cast<std::uint64_t>( bytesRead );

        if( fileSizeAsNumber > 0u )
        {
            calcinfo.percentage = 100.f * static_cast<float>( bytesHashed ) / static_cast<float>( fileSizeAsNumber );
            MessageSystem<SBigMD5FileCalc>::getInstance().send( calcinfo );
        }
    }

    calcinfo.percentage = 100.f;
    calcinfo.Progress = true;
    MessageSystem<SBigMD5FileCalc>::getInstance().send( calcinfo );

    m_md5 = sha256.getHash();
}

void IFile::waitForDiskToBeReady()
{
    const StringWr diskName = m_path.getDiskName();

    constexpr float usageThreshold{ 60.f };
    constexpr std::uint32_t maxWaitMs{ 2000u };
    std::uint32_t waitedMs{ 0u };

    float diskUsage =
        CUL::CDiskInfo::getInstance().getDiskUsage( diskName.getSTDString() );

    while( diskUsage > usageThreshold && waitedMs < maxWaitMs )
    {
        CUL::ThreadUtil::sleepUntil( 4u );
        waitedMs += 4u;
        diskUsage = CUL::CDiskInfo::getInstance().getDiskUsage( diskName.getSTDString() );
    }
}

bool IFile::getIsBigFile() const
{
    constexpr std::uint64_t OneMBinBytes = 1024 * 1024;
    constexpr std::uint64_t bigFileMinimumBytes = 8 * OneMBinBytes;
    const std::uint64_t currentFileSizeBytes = getSizeInBytes();
    return currentFileSizeBytes > bigFileMinimumBytes;
}

std::uint64_t IFile::getSizeInBytes() const
{
    if( m_sizeInBytes )
    {
        return *m_sizeInBytes;
    }

    calculateSizeBytes();
    return *m_sizeInBytes;
}

const StringWr& IFile::getSizeBytes_str() const
{
    return m_sizeBytesStr;
}

void IFile::calculateSizeBytes() const
{
    m_sizeBytesStr = p_cullInterface->getFS()->getFileSize( m_path );
    m_sizeInBytes = m_sizeBytesStr.toUint64();
}

void IFile::loadBackground( bool keepLineEndingCharacter,
                            bool removeBottomEmptyLines,
                            std::function<void( void )> finishCallback )
{
    waitForBackgroundLoad();
    m_backgroundLoadThread = std::make_unique<ThreadWrapper>(
        [finishCallback, keepLineEndingCharacter, removeBottomEmptyLines, this]()
        {
            load( keepLineEndingCharacter, removeBottomEmptyLines );
            if( finishCallback )
            {
                finishCallback();
            }

            m_loaded = true;
        } );
    m_backgroundLoadThread->run();
}

void IFile::waitForBackgroundLoad()
{
    if( m_backgroundLoadThread )
    {
        m_backgroundLoadThread->waitForCompletion();
        m_backgroundLoadThread.reset( nullptr );
    }
}

bool IFile::getIsLoaded() const
{
    return m_loaded;
}

IFile::~IFile()
{
    waitForBackgroundLoad();
}

#if defined( DEBUG_THIS_FILE )
    #if defined( CUL_COMPILER_MSVC )
        #pragma optimize( "", on )
    #elif defined( CUL_COMPILER_CLANG )
        #pragma clang optimize on
    #elif defined( CUL_COMPILER_GCC )
        #pragma GCC pop_options
    #endif
#endif  // #if defined(DEBUG_THIS_FILE)
