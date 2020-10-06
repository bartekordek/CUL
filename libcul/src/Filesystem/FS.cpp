#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "Filesystem/FSUtils.hpp"

using namespace CUL;
using namespace FS;

using FF = FileFactory;

bool isRegularFile( const char* path );
bool isRegularFile( const wchar_t* path );

bool isDirectory( const char* path );
bool isDirectory( const wchar_t* path );

FSApi::FSApi()
{
}

FSApi::~FSApi()
{
}

String FSApi::getCurrentDir()
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    auto currentDir = std::experimental::filesystem::current_path();
#else
    auto currentDir = std::filesystem::current_path();
#endif
    FsPath full_path( currentDir );
    return full_path.string();
}

IFile* FSApi::getDirectory( const Path& directory )
{
    Directory* result = new Directory( directory );
    FsPath directoryBf( directory.getPath().cStr() );
    using DI = DirectoryIterator;
    DI end;
    for( DI it( directoryBf ); it != end; ++it )
    {
        const auto pathIt = it->path();
        const auto filePath = pathIt.string();
        Path path = filePath;
        if( isRegularFile( filePath.c_str() ) )
        {
            auto child = FF::createFileFromPath( path );
            result->addChild( child );
        }
        else if( isDirectory( filePath.c_str() ) )
        {
            auto nestedDirectory = getDirectory( path );
            result->addChild( nestedDirectory );
        }
    }

    return result;
}

bool isRegularFile( const char* path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_regular_file( path );
#else
    return std::filesystem::is_regular_file( path );
#endif
}

bool isRegularFile( const wchar_t* path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_regular_file( path );
#else
    return std::filesystem::is_regular_file( path );
#endif
}


bool isDirectory( const char* path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_directory( path );
#else
    return std::filesystem::is_directory( path );
#endif
}

bool isDirectory( const wchar_t* path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_directory( path );
#else
    return std::filesystem::is_directory( path );
#endif
}
