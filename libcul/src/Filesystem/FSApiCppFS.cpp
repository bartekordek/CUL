#include "Filesystem/FSApiCppFS.hpp"

#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/CULInterface.hpp"

#include "Filesystem/IMPORT_fscpp.hpp"
#include "CUL/STL_IMPORTS/STD_filesystem.hpp"
#include "Filesystem/FSUtils.hpp"

using namespace CUL;
using namespace FS;

FSApiCppFS::FSApiCppFS(FileFactory* ff, CULInterface* culInterface):
    m_fileFactory( ff ),
    m_culInterface( culInterface )
{

}

std::vector<Path> FSApiCppFS::ListAllFiles(const Path& directory)
{
    std::vector<Path> result;

    cppfs::FileHandle dir = cppfs::fs::open( directory.getPath().string() );

    if( dir.isDirectory() )
    {
        for( cppfs::FileIterator it = dir.begin(); it != dir.end(); ++it )
        {
            std::string path = directory.getPath().string() + "/" + * it;
            cppfs::FileHandle file = cppfs::fs::open( path );

            if( file.isDirectory() )
            {
                std::vector<Path> dirFiles = ListAllFiles( path );
                for( const auto& fileFile: dirFiles )
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

bool FSApiCppFS::isDirectory(const Path& path)
{
    cppfs::FileHandle file = cppfs::fs::open( path.getPath().string() );

    bool result = file.isDirectory();
    return result;
}

bool FSApiCppFS::fileExist(const Path& path)
{
    cppfs::FileHandle file = cppfs::fs::open( path.getPath().string() );
    bool result = file.exists();
    return result;
}

TimeConcrete FSApiCppFS::getLastModificationTime(const Path& path)
{
    cppfs::FileHandle file = cppfs::fs::open( path.getPath().string() );
    TimeConcrete tc;
    tc.setTimeUs( file.modificationTime() );
    return tc;
}

String FSApiCppFS::getFileSize( const Path& )
{
    return String();
}

TimeConcrete FSApiCppFS::getCreationTime(const Path&)
{
    TimeConcrete tc;
    // TODO:
    return tc;
}

IFile* FSApiCppFS::getDirectory(const Path&)
{
    //TODO:
    return nullptr;
}

String FSApiCppFS::getCurrentDir()
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    auto currentDir = std::experimental::filesystem::current_path();
#else
    auto currentDir = std::filesystem::current_path();
#endif
    FsPath full_path( currentDir );
    return full_path.string();
}

FSApiCppFS::~FSApiCppFS()
{

}