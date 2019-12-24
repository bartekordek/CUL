#pragma once

#include "CUL/CUL.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/UselessMacros.hpp"

using Cunt = const unsigned int;

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

class CULLib_API IFile
{
public:
    IFile( void );
    IFile( CsStr& fPath ) = delete;
    IFile( const IFile& file ) = delete;
    virtual ~IFile();

    IFile& operator=( CsStr& rPath ) = delete;

    virtual const Path& getPath() const = 0;

    virtual CBool exists() const = 0;
    virtual CBool isBinary() const = 0;

    virtual void changePath( const Path& newPath ) = 0;

    virtual void reload( CBool keepLineEndingCharacter = false ) = 0;
    virtual void load( CBool keepLineEndingCharacter = false ) = 0;
    virtual void unload() = 0;

    virtual CsStr& firstLine() const = 0;
    virtual CsStr& lastLine() const = 0;

    virtual CsStr& getAsOneString() const = 0;
    virtual const char** getContent() const = 0;

    virtual Cunt getLinesCount() const = 0;

protected:
private:
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )
