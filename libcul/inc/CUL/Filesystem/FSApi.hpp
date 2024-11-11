#pragma once

#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/Path.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

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

    String getCurrentDir();
    IFile* getDirectory( const Path& directory );

    void getCreationTime( const Path& path, Time& outValue );
    void getLastModificationTime( const Path& path, Time& outValue );
    String getFileSize( const Path& path );

    bool fileExist( const Path& path );
    bool isDirectory( const Path& path );
    bool isRegularFile( const String& path );

    std::vector<Path> ListAllFiles( const Path& directory );
    void ListAllFiles( const Path& directory, std::function<void( const Path& path )> callback );

    void deleteFile( const Path& path );

    ~FSApi();

protected:
private:
    CULInterface* m_culInterface = nullptr;
    FS::FileFactory* m_fileFactory = nullptr;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )