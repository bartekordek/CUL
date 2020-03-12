#pragma once

#include "CUL/CUL.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"

using Cunt = const unsigned int;
using Cbool = const bool;

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

enum class FileType: short
{
    NONE = 0,
    TXT,
    BINARY,
    DIRECTORY,
    INVALID
};

class CULLib_API IFile;

using FileList = std::set<IFile*>;

class CULLib_API IFile
{
public:
    IFile();

    virtual const Path& getPath() const = 0;
    Cbool exists() const;
    virtual void changePath( const Path& newPath ) = 0;
    virtual void reload( Cbool keepLineEndingCharacter = false ) = 0;
    virtual void load( Cbool keepLineEndingCharacter = false ) = 0;
    virtual void unload() = 0;

    virtual CsStr& firstLine() const = 0;
    virtual CsStr& lastLine() const = 0;

    virtual CsStr& getAsOneString() const = 0;
    virtual const char** getContent() const = 0;

    virtual Cunt getLinesCount() const = 0;

    virtual const FileType getType() const = 0;
    const FileList& getChildList() const;
    void addChild( IFile* file );

    const bool operator==( const IFile* arg ) const;
    const bool operator<( const IFile* arg ) const;

    virtual ~IFile();

protected:
private:
    FileList m_fileList;

private: // Deleted:
    IFile( CsStr& fPath ) = delete;
    IFile( const IFile& file ) = delete;
    IFile( IFile&& file ) = delete;
    IFile& operator=( CsStr& rPath ) = delete;
    IFile& operator=( const IFile& file ) = delete;
    IFile& operator=( IFile&& file ) = delete;

};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )