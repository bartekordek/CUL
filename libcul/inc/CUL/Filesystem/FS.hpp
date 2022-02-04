#pragma once

#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/TimeConcrete.hpp"
#include "CUL/String.hpp"

#include "CUL/STL_IMPORTS/STD_set.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

class CULLib_API FSApi
{
public:
    FSApi( FileFactory* ff, CULInterface* culInterface );

    String getCurrentDir();
    IFile* getDirectory( const Path& directory );
    TimeConcrete getCreationTime( const Path& path );
    TimeConcrete getLastModificationTime( const Path& path );
    bool fileExist( const Path& path );
    static bool isDirectory( const Path& path );

    std::vector<Path> ListAllFiles( const Path& directory );

    virtual ~FSApi();
protected:
private:
    FileFactory* m_fileFactory = nullptr;
    CULInterface* m_culInterface = nullptr;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )