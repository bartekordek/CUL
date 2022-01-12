#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/CULInterface.hpp"
#include "Filesystem/FSUtils.hpp"
#include "CUL/TimeConcrete.hpp"

using namespace CUL;
using namespace FS;

using FF = FileFactory;

bool isRegularFile( const char* path );
bool isRegularFile( const wchar_t* path );

bool isDirectory( const char* path );
bool isDirectory( const wchar_t* path );

FSApi::FSApi( FileFactory* ff, CULInterface* culInterface ):
    m_fileFactory( ff ),
    m_culInterface( culInterface )
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
    Directory* result = new Directory( directory, m_culInterface );
    FsPath directoryBf( directory.getPath().cStr() );
    using DI = DirectoryIterator;
    DI end;
    for( DI it( directoryBf ); it != end; ++it )
    {
        const auto& pathIt = it->path();
        const auto filePath = pathIt.string();
        if( isRegularFile( filePath.c_str() ) )
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
TimeConcrete FSApi::getCreationTime( const Path& )
{
    return TimeConcrete();
}

std::vector<Path> FSApi::ListAllFiles( const Path& directory )
{
    std::vector<Path> result;
    for( const auto& entry : std::filesystem::recursive_directory_iterator( directory.getPath().string() ) )
    {
        const auto& entryPath = entry.path();
        std::string pathAsString = entryPath.string();

        Path culPath = pathAsString;
        result.push_back( culPath );
    }
    return result;
}

TimeConcrete FSApi::getLastModificationTime( const Path& path )
{
    if( false == m_culInterface->getFS()->fileExist( path ) )
    {
        return TimeConcrete();
    }

    TimeConcrete timeConcrete;
    const auto ftime = FSCpp::last_write_time( path.getPath().cStr() );
    const auto timeSinceEpoch = ftime.time_since_epoch();
    const auto count = timeSinceEpoch.count();
    const auto seconds = count * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
    const auto microSeconds = seconds * 100000;
    timeConcrete.setTimeUs( (unsigned int) microSeconds );
    return timeConcrete;
}

bool FSApi::fileExist( const Path& path )
{
    return isRegularFile( path.getPath().cStr() );
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


FSApi::~FSApi()
{
}