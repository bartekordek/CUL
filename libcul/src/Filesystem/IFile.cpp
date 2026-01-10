#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Threading/ThreadUtil.hpp"
#include "CUL/Threading/ThreadWrap.hpp"

#include "CUL/CULInterface.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/Hardware/DiskInfo.hpp"
#include <CUL/ITimer.hpp>
#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_iterator.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "IMPORT_hash_library.hpp"

using namespace CUL;
using namespace FS;

#if 0 // DEBUG_THIS_FILE, set 0->1 to debug
    #define DEBUG_THIS_FILE 1

    #if defined(CUL_COMPILER_MSVC)
        #pragma optimize( "", off )
    #elif defined(CUL_COMPILER_CLANG)
        #pragma clang optimize off
    #elif defined(CUL_COMPILER_GCC)
        #pragma GCC push_options
        #pragma GCC optimize( "O0" )
    #endif
#endif

IFile::IFile( const String& fPath, CUL::CULInterface* inInterface ) : p_cullInterface( inInterface ), m_path( fPath )
{
    p_cullInterface->getFS()->getLastModificationTime( fPath, m_lastModificationTime );
    calculateSizeBytes();
}

void IFile::setPath( const String& fPath )
{
    m_path = fPath;
    calculateSizeBytes();
}

void IFile::addLine( const String& )
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

void IFile::loadFromString( const String& /*contents*/, bool /*keepLineEndingCharacter = false */ )
{
    throw std::logic_error( "Method not implemented" );
}

void IFile::loadFromStringNoEmptyLines( const String& /*contents*/, bool /*keepLineEndingCharacter*/ )
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
        p_cullInterface->getFS()->getLastModificationTime( m_path, m_lastModificationTime );
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

const String& IFile::getMD5()
{
    if( m_md5.empty() )
    {
        calculateMD5();
    }
    return m_md5;
}

void IFile::calculateMD5()
{
    const std::uint64_t currentFileSizeBytes = getSizeBytes().toUint64();

    const char* pathChar = getPath().getPath().cStr();
    CUL::ThreadUtil::getInstance().setThreadStatusArgs( "[IFile::calculateMD5] File: %s wait for disk...", pathChar );
    waitForDiskToBeReady();
    CUL::ThreadUtil::getInstance().setThreadStatusArgs( "[IFile::calculateMD5] File: %s wait for disk... done.", pathChar );

    if( getIsBigFile() )
    {
        LOG::ILogger::getInstance().log( "[IFile::calculateMD5] Big file: " + getPath().getPath() );

        std::ifstream file( m_path.getPath().getString(), std::ios::binary );
        file.unsetf( std::ios::skipws );

        constexpr size_t bytesPerRead = 131072;

        char buffor[bytesPerRead];
        std::array<uint8_t, 4> value;
        value[0] = 0u;
        value[1] = 0u;
        value[2] = 0u;
        value[3] = 0u;
        void* ptr = &buffor;
        constexpr std::size_t sizeofChar = sizeof( char );
        constexpr std::size_t sizeofBuffor = sizeofChar * bytesPerRead;
        constexpr std::size_t howManyCharacters = sizeofBuffor / sizeofChar;

        std::memset( &buffor, 0, sizeofBuffor );
        const auto size = file.tellg();
        SHA256 sha256;
        uint64_t it = 0u;
        float coef = 0.f;
        const auto threadId = CUL::ThreadUtil::getInstance().getCurrentThreadId();
        unsigned percentage = 0u;
        while( file.read( buffor, howManyCharacters ) )
        {
            sha256.add( ptr, bytesPerRead );
            ++it;
            coef = static_cast<float>( bytesPerRead * it ) / static_cast<float>( currentFileSizeBytes );
            percentage = static_cast<unsigned>( 100.f * coef );
            const String pathString = getPath().getPath().string();

            constexpr std::size_t bufferSize{ 512 };
            char name[bufferSize];
            snprintf( name, bufferSize, "[IFile::calculateMD5] Big file: %s, %d %%", pathString.cStr(), percentage );

            CUL::ThreadUtil::getInstance().setThreadStatus( name, &threadId );
        }
        m_md5 = sha256.getHash();
        file.close();
    }
    else
    {
        std::ifstream file( m_path.getPath().getString(), std::ios::binary );
        file.unsetf( std::ios::skipws );

        unsigned fileSizeAsNumber = getSizeBytes().toUint64();
        std::vector<unsigned char> vec;
        vec.reserve( fileSizeAsNumber );
        vec.insert( vec.begin(), std::istream_iterator<unsigned char>( file ), std::istream_iterator<unsigned char>() );
        if( vec.empty() == false )
        {
            SHA256 sha256;
            m_md5 = sha256( vec.data(), fileSizeAsNumber );
        }
        
        file.close();
    }
}

void IFile::waitForDiskToBeReady()
{
    const String diskName = m_path.getDiskName();

    constexpr float usageThreshold{ 60.f };
    float diskUsage = CUL::CDiskInfo::getInstance().getDiskUsage( diskName.string() );

    if( diskUsage <= usageThreshold )
    {
        return;
    }

    do
    {
        CUL::ITimer::sleepMiliSeconds( 1000u );
        const float diskUsage = CUL::CDiskInfo::getInstance().getDiskUsage( diskName.string() );
        if( diskUsage <= usageThreshold )
        {
            return;
        }
    } while( true );
}

bool IFile::getIsBigFile() const
{
    constexpr std::uint64_t OneMBinBytes = 1024 * 1024;
    constexpr std::uint64_t bigFileMinimumBytes = 16 * OneMBinBytes;
    const std::uint64_t currentFileSizeBytes = getSizeBytes().toUint64();
    return currentFileSizeBytes > bigFileMinimumBytes;
}

const String& IFile::getSizeBytes() const
{
    return m_sizeBytes;
}

void IFile::calculateSizeBytes()
{
    m_sizeBytes = p_cullInterface->getFS()->getFileSize( m_path );
}

void IFile::loadBackground( bool keepLineEndingCharacter, bool removeBottomEmptyLines, std::function<void( void )> finishCallback )
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
    #if defined(CUL_COMPILER_MSVC)
        #pragma optimize( "", on )
    #elif defined( CUL_COMPILER_CLANG)
        #pragma clang optimize on
    #elif defined( CUL_COMPILER_GCC)
        #pragma GCC pop_options
    #endif
#endif  // #if defined(DEBUG_THIS_FILE)
