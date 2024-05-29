#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/CULInterface.hpp"

#include "CUL/STL_IMPORTS/STD_exception.hpp"
#include "CUL/STL_IMPORTS/STD_filesystem.hpp"

using namespace CUL;
using namespace FS;

#define USE_CPPFS 0

FSApi::FSApi( CULInterface* cul, FS::FileFactory* ff ) :
    m_culInterface( cul ),
    m_fileFactory( ff )
{
}

#if USE_CPPFS

String FSApi::getCurrentDir()
{
    throw std::logic_error( "Method not implemented" );
    return String();
}

IFile* FSApi::getDirectory( const Path& directory )
{
    throw std::logic_error( "Method not implemented" );
    return nullptr;
}

void FSApi::getCreationTime( const Path& path, Time& outValue )
{
    throw std::logic_error( "Method not implemented" );
}

void FSApi::getLastModificationTime( const Path& path, Time& outValue )
{
    cppfs::FileHandle file = cppfs::fs::open( path.getPath().string() );
    TimeConcrete tc;
    tc.setTimeUs( file.modificationTime() );
    return tc;
}

String FSApi::getFileSize( const Path& path )
{
    throw std::logic_error( "Method not implemented" );
    return String();
}

bool FSApi::fileExist( const Path& path )
{
    cppfs::FileHandle file = cppfs::fs::open( path.getPath().string() );
    bool result = file.exists();
    return result;
}

bool FSApi::isDirectory( const Path& path )
{
    cppfs::FileHandle file = cppfs::fs::open( path.getPath().string() );

    bool result = file.isDirectory();
    return result;
}

std::vector<Path> FSApi::ListAllFiles( const Path& directory )
{
    std::vector<Path> result;

    cppfs::FileHandle dir = cppfs::fs::open( directory.getPath().string() );

    if( dir.isDirectory() )
    {
        for( cppfs::FileIterator it = dir.begin(); it != dir.end(); ++it )
        {
            std::string path = directory.getPath().string() + "/" + *it;
            cppfs::FileHandle file = cppfs::fs::open( path );

            if( file.isDirectory() )
            {
                std::vector<Path> dirFiles = ListAllFiles( path );
                for( const auto& fileFile : dirFiles )
                {
                    result.push_back( fileFile );
                }
            }
            else
            {
                Path r_path = path;
                result.push_back( r_path );
            }
        }
    }


    return result;
}

FSApi::~FSApi()
{
}


#else  // #if USE_CPPFS

std::vector<Path> FSApi::ListAllFiles( const Path& directory )
{
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
        bool isDir = isDirectory( culPath );
        culPath.setIsDir( isDir );

        result.push_back( culPath );
    }

    return result;
}


void FSApi::ListAllFiles( const Path& directory, std::function<void( const Path& path )> callback )
{
    std::vector<Path> result;

    const auto dir = directory.getPath().string();
    std::error_code errorCode;
    for( const auto& entry :
         std::filesystem::recursive_directory_iterator( dir, std::filesystem::directory_options::skip_permission_denied, errorCode ) )
    {
        if( errorCode.value() != 0 )
        {
            CUL::Assert::simple( false, errorCode.message() );
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
        bool isDir = isDirectory( culPath );
        culPath.setIsDir( isDir );

        callback( culPath );
    }
}

bool FSApi::isDirectory( const Path& path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_directory( path );
#else
    std::error_code ec;
    bool result = std::filesystem::is_directory( path.getPath().getChar(), ec );
    return result;
#endif
}

void FSApi::getCreationTime( const Path&, Time& )
{
    throw std::logic_error( "Method not implemented" );
}

template <typename TP>
std::time_t to_time_t( TP tp )
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>( tp - TP::clock::now() + system_clock::now() );
    return system_clock::to_time_t( sctp );
}

void FSApi::getLastModificationTime( const Path& inPath, Time& outTime )
{
    if( false == m_culInterface->getFS()->fileExist( inPath ) )
    {
        return;
    }

#if defined( CUL_WINDOWS )
    std::filesystem::path p = inPath.getPath().wCstr();
#else
    std::filesystem::path p = inPath.getPath().cStr();
#endif
    std::filesystem::file_time_type ftime = std::filesystem::last_write_time( p );
    std::uint64_t timeConverted = static_cast<std::uint64_t>( to_time_t( ftime ) );
    outTime.setTimeSec( timeConverted );
}

bool FSApi::fileExist( const Path& path )
{
    return isRegularFile( path );
}

String FSApi::getCurrentDir()
{
    auto currentDir = std::filesystem::current_path();
    const std::filesystem::path full_path( currentDir );
    return full_path.string();
}

IFile* FSApi::getDirectory( const Path& directory )
{
    Directory* result = new Directory( directory, m_culInterface );
    std::filesystem::path directoryBf( directory.getPath().cStr() );
    using DI = std::filesystem::directory_iterator;
    DI end;
    for( DI it( directoryBf ); it != end; ++it )
    {
        const auto& pathIt = it->path();
        const auto filePath = pathIt.string();
        if( isRegularFile( filePath ) )
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

bool FSApi::isRegularFile( const String& path )
{
    std::error_code existsErrorCode;
    bool result = std::filesystem::is_regular_file( path.getString(), existsErrorCode );
    if( existsErrorCode.value() != 0 )
    {
        LOG::ILogger::getInstance()->log( "[" + String( path ) + "] " + existsErrorCode.message() );
    }
    return result;
}

String FSApi::getFileSize( const Path& path )
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
                CUL::Assert::simple( false, isRegularFileCheck.message() );
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

FSApi::~FSApi()
{
}
#endif  // #if USE_CPPFS