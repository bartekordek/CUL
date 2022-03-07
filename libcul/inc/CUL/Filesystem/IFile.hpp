#pragma once

#include "CUL/Filesystem/Path.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"
#include "CUL/TimeConcrete.hpp"

NAMESPACE_BEGIN( CUL )
class CULInterface;
NAMESPACE_BEGIN( FS )

enum class FileType : short
{
    NONE = 0,
    TXT,
    BINARY,
    DIRECTORY,
    INVALID
};

class CULLib_API IFile;

using FileList = std::set<GUTILS::DumbPtr<IFile>>;

class CULLib_API IFile
{
public:
    IFile( const String& fPath, CUL::CULInterface* interface );

    void setPath( const String& fPath );
    virtual void addLine( const String& line);
    virtual void saveFile();

    virtual const Path& getPath() const = 0;
    bool exists() const;
    virtual void changePath( const Path& newPath ) = 0;
    virtual void reload( bool keepLineEndingCharacter = false ) = 0;
    virtual void load( bool keepLineEndingCharacter = false ) = 0;
    virtual void unload() = 0;

    TimeConcrete getCreationTime();
    TimeConcrete getLastModificationTime();

    const String& getMD5();
    unsigned getSizeBytes();

    virtual const String& firstLine() const = 0;
    virtual const String& lastLine() const = 0;

    virtual const String& getAsOneString() const = 0;
    virtual const char** getContent() const = 0;

    virtual unsigned getLinesCount() const = 0;

    virtual FileType getType() const = 0;
    const FileList& getChildList() const;
    void addChild( IFile* file );

    virtual void loadFromString( const String& contents );

    bool operator==( const IFile& arg ) const;
    bool operator<( const IFile& arg ) const;
    bool operator>( const IFile& arg ) const;

    virtual ~IFile();

protected:
    CUL::CULInterface* p_cullInterface = nullptr;

private:
    void calculateMD5();
    void calculateSizeBytes();
    FileList m_fileList;
    String m_path;
    String m_md5;

    TimeConcrete m_creationTime;
    TimeConcrete m_lastModificationTime;

    unsigned m_sizeBytes = 0u;

private:  // Deleted:
    IFile() = delete;
    IFile( const IFile& file ) = delete;
    IFile( IFile&& file ) = delete;
    IFile& operator=( const String& rPath ) = delete;
    IFile& operator=( const IFile& file ) = delete;
    IFile& operator=( IFile&& file ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )