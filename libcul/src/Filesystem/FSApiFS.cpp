#include "Filesystem/FSApiFS.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/CULInterface.hpp"
#include "Filesystem/FSUtils.hpp"
#include "CUL/TimeConcrete.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_chrono.hpp"
#include "CUL/STL_IMPORTS/STD_format.hpp"
#include "CUL/STL_IMPORTS/STD_chrono.hpp"

using namespace CUL;
using namespace FS;


using FF = FileFactory;

bool isRegularFileImpl( const char* path );
bool isRegularFileImpl( const wchar_t* path );
bool isRegularFile( const wchar_t* path );

bool isDirectoryImpl( const FsPath& path );
bool isDirectoryImpl( const wchar_t* path );


FSApiFS::FSApiFS( FileFactory* ff, CULInterface* culInterface ):
    m_fileFactory( ff ),
    m_culInterface( culInterface )
{
}

String FSApiFS::getCurrentDir()
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    auto currentDir = std::experimental::filesystem::current_path();
#else
    auto currentDir = std::filesystem::current_path();
#endif
    FsPath full_path( currentDir );
    return full_path.string();
}

IFile* FSApiFS::getDirectory( const Path& directory )
{
    Directory* result = new Directory( directory, m_culInterface );
    FsPath directoryBf( directory.getPath().cStr() );
    using DI = DirectoryIterator;
    DI end;
    for( DI it( directoryBf ); it != end; ++it )
    {
        const auto& pathIt = it->path();
        const auto filePath = pathIt.string();
        if( isRegularFileImpl( filePath.c_str() ) )
        {
            auto child = m_fileFactory->createFileFromPath( filePath );
            result->addChild( child );
        }
        else if( isDirectory( filePath.c_str() ) )
        {
            auto nestedDirectory = getDirectory( filePath );
            result->addChild( nestedDirectory );
        }
    }

    return result;
}


// TODO:
TimeConcrete FSApiFS::getCreationTime( const Path& )
{
    return TimeConcrete();
}

std::vector<Path> FSApiFS::ListAllFiles( const Path& directory )
{
    setlocale( 0, "Polish" );
    std::vector<Path> result;


    for( const auto& entry : std::filesystem::recursive_directory_iterator( directory.getPath().string(), std::filesystem::directory_options::skip_permission_denied ) )
    {
        const std::filesystem::path entryPath = entry.path();

#ifdef _MSC_VER
        String temp = entryPath.wstring();
        Path culPath = temp;
#else
        Path culPath = entryPath.string();
#endif
        bool isDir = isDirectoryImpl( entryPath );
        culPath.setIsDir( isDir );

        result.push_back( culPath );
    }


    return result;
}

void FSApiFS::ListAllFiles( const Path& directory, std::function<void( const Path& path )> callback )
{
    setlocale( 0, "Polish" );
    std::vector<Path> result;

    const auto dir = directory.getPath().string();
    std::error_code errorCode;
    for( const auto& entry :
         std::filesystem::recursive_directory_iterator( dir, std::filesystem::directory_options::skip_permission_denied, errorCode ) )
    {

        if( errorCode.value() != 0 )
        {
#if defined(CUL_COMPILER_MSVC)
            DebugBreak();
#endif
        }

        const std::filesystem::path entryPath = entry.path();
        String::UnderlyingType tempString = entryPath;

        const std::u32string someString = entryPath.u32string();
#ifdef _MSC_VER
        const String tempPath = entryPath.wstring();
        Path culPath = tempPath;
#else
        Path culPath = entryPath.string();
#endif
        bool isDir = isDirectoryImpl( entryPath );
        culPath.setIsDir( isDir );

        callback( culPath );
    }
}

template <typename TP>
std::time_t to_time_t( TP tp )
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>( tp - TP::clock::now() + system_clock::now() );
    return system_clock::to_time_t( sctp );
}

TimeConcrete FSApiFS::getLastModificationTime( const Path& path )
{
    if( false == m_culInterface->getFS()->fileExist( path ) )
    {
        return TimeConcrete();
    }

    TimeConcrete timeConcrete;

    constexpr std::int32_t SECS_DAY = 60 * 60 * 24;

#if defined( CUL_WINDOWS )
    std::filesystem::path p = path.getPath().wCstr();
#else
    std::filesystem::path p = path.getPath().cStr();
#endif
    std::filesystem::file_time_type ftime = std::filesystem::last_write_time( p );
    const std::time_t timeConverted = to_time_t( ftime );
    timeConcrete.m_ns = timeConverted * 1000000000;

    const std::int32_t dayclock = (std::int32_t)timeConverted % SECS_DAY;
    const std::int32_t dayno = (std::int32_t)timeConverted / SECS_DAY;

    const auto value = dayclock % 60;
    timeConcrete.m_seconds = static_cast<std::uint16_t>( dayclock % 60 );
    timeConcrete.m_minutes = static_cast<std::uint16_t>( ( dayclock % 3600 ) / 60 );
    timeConcrete.m_hours = static_cast<std::uint16_t>( dayclock / 3600 );
    timeConcrete.m_wday = static_cast<std::uint16_t>( ( dayno + 4 ) % 7 ); /* day 0 was a thursday */

    const auto seconds = timeConverted / 1000;
    const auto minutes = seconds / 60;
    const auto hours = minutes / 60;
    const auto days = hours / 24;

    const std::time_t timeT = timeConverted;
    const auto tm = std::localtime( &timeT );

    //const auto dupa = std::asctime( std::localtime( &timeT ) );

    timeConcrete.m_years = static_cast<std::uint16_t>( 1900 + tm->tm_year );
    timeConcrete.m_months = static_cast<std::uint16_t>( ( tm->tm_mon + 1 ) );
    timeConcrete.m_days = static_cast<std::uint16_t>( tm->tm_mday );
    timeConcrete.m_hours = static_cast<std::uint16_t>( tm->tm_hour );
    timeConcrete.m_minutes = static_cast<std::uint16_t>( tm->tm_min );
    timeConcrete.m_seconds = static_cast<std::uint16_t>( tm->tm_sec );

    std::tm ts = *std::localtime( &timeT );
    char buf[80];
    strftime( buf, sizeof( buf ), "%Y-%m-%d %H:%M:%S", &ts );
    timeConcrete.m_asString = buf;
    return timeConcrete;
}

String FSApiFS::getFileSize( const Path& path )
{
    std::error_code ec;

#ifdef _MSC_VER
    const std::filesystem::path filePath = path.getPath().wstring();
    uintmax_t size = std::filesystem::file_size( filePath, ec );

    if( ec.value() != 0 )
    {
        const auto message = ec.message();
        LOG::ILogger::getInstance()->log( message );

        std::error_code symlinkCheckError;
        if( std::filesystem::is_symlink( filePath, symlinkCheckError ) )
        {
            size = 0u;
        }
        else
        {
            std::error_code isRegularFileCheck;
            if( std::filesystem::is_regular_file( filePath, isRegularFileCheck ) == false )
            {
                size = 0u;
            }
            else
            {
#if defined( CUL_COMPILER_MSVC )
                DebugBreak();
#endif
            }
        }
    }
#else
    uintmax_t size = std::filesystem::file_size( path.getPath().string(), ec );
#endif

    const auto string = std::to_string( size );
    String result = string;
    return result;
}

bool FSApiFS::fileExist( const Path& path )
{
    return isRegularFileImpl( path.getPath().getChar() );
}

bool FSApiFS::isDirectory( const Path& path )
{
    FsPath fsPath = path.getPath().cStr();
    return isDirectoryImpl( fsPath );
}

FSApiFS::~FSApiFS()
{
}

bool isRegularFileImpl( const char* path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_regular_file( path );
#else
    return std::filesystem::is_regular_file( path );
#endif
}

bool isRegularFileImpl( const wchar_t* path )
{
    std::error_code existsErrorCode;
    if( std::filesystem::exists( path, existsErrorCode ) == false )
    {
        if( existsErrorCode.value() != 0 )
        {
            LOG::ILogger::getInstance()->log( "[" + String( path ) + "] " + existsErrorCode.message() );
        }
        return false;
    }

#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_regular_file( path );
#else
    std::error_code ec;
    const bool result = std::filesystem::is_regular_file( path, ec );
    const int value = ec.value();
    if( value != 0 )
    {
        if( value == 2 )
        {
            return false;
        }
#if defined( CUL_COMPILER_MSVC )
        const auto message = ec.message();
        LOG::ILogger::getInstance()->log( message );
        DebugBreak();
#endif
    }
    return result;
#endif
}


bool isDirectoryImpl( const FsPath& path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_directory( path );
#else
    std::error_code ec;
    bool result = std::filesystem::is_directory( path, ec );
    return result;
#endif
}

bool isDirectoryImpl( const wchar_t* path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_directory( path );
#else
    return std::filesystem::is_directory( path );
#endif
}

