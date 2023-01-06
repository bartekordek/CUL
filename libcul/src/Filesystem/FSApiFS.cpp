#include "Filesystem/FSApiFS.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/CULInterface.hpp"
#include "Filesystem/FSUtils.hpp"
#include "CUL/TimeConcrete.hpp"


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
    uintmax_t size = std::filesystem::file_size( path.getPath().wstring(), ec );
#else
    uintmax_t size = std::filesystem::file_size( path.getPath().string(), ec );
#endif

    std::error_condition ok;
    if( ec != ok )
    {
        auto x = 0;
    }

    String result = (unsigned)size;
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
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_regular_file( path );
#else
    return std::filesystem::is_regular_file( path );
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

