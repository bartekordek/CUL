#pragma once

#include "CUL/Filesystem/IFile.hpp"
#include "CUL/JSON/INode.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( JSON )

class CULLib_API IJSONFile:
    public FS::IFile
{
public:
    IJSONFile() = default;
    IJSONFile( const IJSONFile& rhv ) = delete;
    virtual ~IJSONFile() = default;

    IJSONFile& operator=( const IJSONFile& rhv ) = delete;

    virtual INode* getRoot() const = 0;


protected:
private:
};

NAMESPACE_END( JSON )
NAMESPACE_END( CUL )