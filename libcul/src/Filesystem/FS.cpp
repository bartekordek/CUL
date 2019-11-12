#include "CUL/Filesystem/FS.hpp"
#include "Filesystem/FSUtils.hpp"

using namespace CUL;
using namespace FS;

const bool isRegularFile( const char* path );
const bool isRegularFile( const wchar_t* path );

FSApi::FSApi()
{
}

FSApi::~FSApi()
{
}

MyString FSApi::getCurrentDir()
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    auto currentDir = std::experimental::filesystem::current_path();
#else
    auto currentDir = std::filesystem::current_path();
#endif
    FsPath full_path( currentDir );
    return full_path.string();
}

const FileList FSApi::getFilesUnderDirectory( const Path& directory )
{
    FileList result;
    FsPath directoryBf( directory.getPath().cStr() );
    using DI = DirectoryIterator;
    DI end;
    for( DI it( directoryBf ); it != end; ++it )
    {
        if( isRegularFile( it->path().c_str() ) )
        {
            MyString filePath = it->path().string();
            result.insert( filePath );
        }
    }

    return result;
}

const bool isRegularFile( const char* path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_regular_file( path );
#else
    return std::filesystem::is_regular_file( path );
#endif
}

const bool isRegularFile( const wchar_t* path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_regular_file( path );
#else
    return std::filesystem::is_regular_file( path );
#endif
}
