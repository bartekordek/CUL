#pragma once

#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/TimeConcrete.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

NAMESPACE_BEGIN( CUL )
class CULInterface;
NAMESPACE_BEGIN( FS )
class FileFactory;
class IFile;


class CULLib_API FSApi
{
public:
    // FSApiFS
    // FSApiCppFS
    // ?
    static FSApi* crateInstance(const CUL::String& type, FileFactory* ff, CULInterface* culInterface);

    FSApi();

    virtual String getCurrentDir() = 0;
    virtual IFile* getDirectory( const Path& directory ) = 0;

    virtual TimeConcrete getCreationTime( const Path& path ) = 0;
    virtual TimeConcrete getLastModificationTime( const Path& path ) = 0;
    virtual String getFileSize( const Path& path ) = 0;

    virtual bool fileExist( const Path& path ) = 0;
    virtual bool isDirectory( const Path& path ) = 0;

    virtual std::vector<Path> ListAllFiles( const Path& directory ) = 0;
    virtual void ListAllFiles( const Path& directory, std::function<void(const Path& path)> callback ) = 0;

    virtual ~FSApi();
protected:
private:

};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )