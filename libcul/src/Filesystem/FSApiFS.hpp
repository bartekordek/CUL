#pragma once

#include "CUL/Filesystem/FSApi.hpp"

NAMESPACE_BEGIN( CUL )

class CULInterface;

NAMESPACE_BEGIN( FS )

class FSApiFS final: public FSApi
{
public:
    FSApiFS(FileFactory* ff, CULInterface* culInterface);

    ~FSApiFS();
protected:
private:
    String getCurrentDir() override;
    IFile* getDirectory( const Path& directory ) override;
    TimeConcrete getCreationTime( const Path& path ) override;
    TimeConcrete getLastModificationTime( const Path& path ) override;
    String getFileSize( const Path& path ) override;
    bool fileExist( const Path& path ) override;
    bool isDirectory( const Path& path ) override;
    std::vector<Path> ListAllFiles( const Path& directory ) override;

    FileFactory* m_fileFactory = nullptr;
    CULInterface* m_culInterface = nullptr;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )