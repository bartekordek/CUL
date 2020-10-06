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
    IFile( CsStr& fPath );

    void setPath(CsStr& fPath);

    virtual const Path& getPath() const = 0;
    bool exists() const;
    virtual void changePath( const Path& newPath ) = 0;
    virtual void reload( Cbool keepLineEndingCharacter = false ) = 0;
    virtual void load( Cbool keepLineEndingCharacter = false ) = 0;
    virtual void unload() = 0;

    virtual CsStr& firstLine() const = 0;
    virtual CsStr& lastLine() const = 0;

    virtual CsStr& getAsOneString() const = 0;
    virtual const char** getContent() const = 0;

    virtual unsigned getLinesCount() const = 0;

    virtual FileType getType() const = 0;
    const FileList& getChildList() const;
    void addChild( IFile* file );

    bool operator==( const IFile* arg ) const;
    bool operator<( const IFile* arg ) const;

    virtual ~IFile();

protected:

private:
    FileList m_fileList;
    String m_path;

private: // Deleted:
    IFile() = delete;
    IFile( const IFile& file ) = delete;
    IFile( IFile&& file ) = delete;
    IFile& operator=( CsStr& rPath ) = delete;
    IFile& operator=( const IFile& file ) = delete;
    IFile& operator=( IFile&& file ) = delete;

};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )