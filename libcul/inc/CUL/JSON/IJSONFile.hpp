#pragma once

#include "CUL/Filesystem/IFile.hpp"
#include "CUL/JSON/INode.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

class CULLib_API IJSONFile:
    public FS::IFile
{
public:
    IJSONFile( const String& path, CULInterface* inInterface );

    virtual INode* getRoot() const = 0;

    virtual ~IJSONFile();

protected:
private:

private: // Deleted.
    IJSONFile( const IJSONFile& rhv ) = delete;
    IJSONFile( IJSONFile&& rhv ) = delete;
    IJSONFile& operator=( const IJSONFile& rhv ) = delete;
    IJSONFile& operator=( IJSONFile&& rhv ) = delete;
};

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )
