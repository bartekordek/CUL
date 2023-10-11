#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Threading/ThreadUtil.hpp"

#include "CUL/CULInterface.hpp"
#include "CUL/TimeConcrete.hpp"
#include "CUL/Log/ILogger.hpp"
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

IFile::IFile( const String& fPath, CUL::CULInterface* interface ) : p_cullInterface( interface ), m_path( fPath )
{
    m_lastModificationTime = p_cullInterface->getFS()->getLastModificationTime( fPath );
}

void IFile::setPath( const String& fPath )
{
    m_path = fPath;
}

void IFile::addLine( const String& )
{
}

void IFile::saveFile()
{
}

void IFile::loadFromString( const String& )
{

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

TimeConcrete IFile::getCreationTime()
{
    return m_creationTime;
}

TimeConcrete IFile::getLastModificationTime()
{
    if( m_lastModificationTime.getUs() > 0u )
    {
        return m_lastModificationTime;
    }

    if( p_cullInterface->getFS()->fileExist( m_path ) )
    {
        m_lastModificationTime = p_cullInterface->getFS()->getLastModificationTime( m_path );
    }
    return m_lastModificationTime;
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
    constexpr std::uint64_t OneMBinBytes = 1024 * 1024;
    constexpr std::uint64_t bigFileMinimumBytes = 64 * OneMBinBytes;
    const std::uint64_t currentFileSizeBytes = getSizeBytes().toUInt();
    const bool isBigFile = currentFileSizeBytes > bigFileMinimumBytes;

    if( isBigFile )
    {
        LOG::ILogger::getInstance()->log( "[IFile::calculateMD5] Big file: " + getPath().getPath() );
        std::ifstream file( m_path.getString(), std::ios::binary );
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
            CUL::ThreadUtil::getInstance().setThreadStatus(
                "[IFile::calculateMD5] Big file: " + getPath().getPath() + ", " + percentage + "%", &threadId );
        }
        m_md5 = sha256.getHash();
        file.close();
    }
    else
    {
        std::ifstream file( m_path.getString(), std::ios::binary );
        file.unsetf( std::ios::skipws );

        unsigned fileSizeAsNumber = getSizeBytes().toUInt();
        std::vector<unsigned char> vec;
        vec.reserve( fileSizeAsNumber );
        vec.insert( vec.begin(), std::istream_iterator<unsigned char>( file ), std::istream_iterator<unsigned char>() );

        SHA256 sha256;
        m_md5 = sha256( vec.data(), fileSizeAsNumber );
        file.close();
    }

    return;
}

const String& IFile::getSizeBytes()
{
    if( m_sizeBytes.empty() )
    {
        calculateSizeBytes();
    }
    return m_sizeBytes;
}

void IFile::calculateSizeBytes()
{
    m_sizeBytes = p_cullInterface->getFS()->getFileSize( m_path );
}

IFile::~IFile()
{
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