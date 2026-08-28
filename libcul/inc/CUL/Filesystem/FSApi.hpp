#pragma once

#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/Path.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include <CUL/STL_IMPORTS/STD_system_error.hpp>
#include "CUL/STL_IMPORTS/STD_filesystem.hpp"

#undef deleteFile

NAMESPACE_BEGIN( CUL )
class CULInterface;
class Time;
NAMESPACE_BEGIN( FS )
class FileFactory;
class IFile;

class CULLib_API FSApi final
{
public:
    // FSApiFS
    // ?

    FSApi( CULInterface* cul, FS::FileFactory* ff );
    FSApi( const FSApi& ) = delete;
    FSApi( FSApi&& ) = delete;
    FSApi& operator=( const FSApi& ) = delete;
    FSApi& operator=( FSApi&& ) = delete;

    StringWr getCurrentDir();
    IFile* getDirectory( const Path& directory );

    void getCreationTime( const Path& path, Time& outValue );
    void getLastModificationTime( const Path& path, Time& outValue );
    StringWr getFileSize( const Path& path );

    bool fileExist( const Path& path );
    bool fileExist( const StringWr& path );
    bool isDirectory( const Path& path );
    bool isRegularFile( const StringWr& path );

    std::vector<Path> ListAllFiles( const Path& directory );
    std::vector<Path> ListAllFiles( const Path& directory, const StringWr& word );
    void ListAllFiles( const Path& directory, std::function<void( const Path& path )> callback );
    static void handleErrorCode( const std::error_code& inErrorCode, const char* inPath );

    static void copy( const Path& inSource,
                      const Path& inTarget,
                      bool inRecursive,
                      bool inAutoOverwrite );
    void deleteFile( const Path& path );
    void deleteFile( const StringWr& path );

    ~FSApi();

protected:
private:
    void iterateThrought( const std::filesystem::directory_entry& de, std::function<void( const Path& path )> callback );
    CULInterface* m_culInterface = nullptr;
    FS::FileFactory* m_fileFactory = nullptr;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )