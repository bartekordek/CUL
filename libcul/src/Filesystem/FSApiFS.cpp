#include "Filesystem/FSApiFS.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/CULInterface.hpp"
#include "Filesystem/FSUtils.hpp"
#include "CUL/TimeConcrete.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

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
        Path culPath = entryPath.wstring();
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

#ifdef _MSC_VER
        Path culPath = entryPath.wstring();
#else
        Path culPath = entryPath.string();
#endif
        bool isDir = isDirectoryImpl( entryPath );
        culPath.setIsDir( isDir );

        callback( culPath );
    }
}

TimeConcrete FSApiFS::getLastModificationTime( const Path& path )
{
    if( false == m_culInterface->getFS()->fileExist( path ) )
    {
        return TimeConcrete();
    }

    TimeConcrete timeConcrete;
    std::filesystem::path asPath = path.getPath().getString();
    const auto ftime = FSCpp::last_write_time( asPath );
    const auto timeSinceEpoch = ftime.time_since_epoch();
    const auto count = timeSinceEpoch.count();
    const auto seconds = count * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
    const auto microSeconds = seconds * 100000;
    timeConcrete.setTimeUs( (unsigned int) microSeconds );
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

