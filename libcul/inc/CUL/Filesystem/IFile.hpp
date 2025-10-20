#pragma once

#include "CUL/Filesystem/Path.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"
#include "CUL/Time.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )
class CULInterface;
class ThreadWrapper;
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
    IFile( const String& fPath, CUL::CULInterface* inInterface );

    void setPath( const String& fPath );
    virtual void addLine( const String& line );
    virtual void saveFile();

    virtual const Path& getPath() const = 0;
    bool exists() const;
    virtual void changePath( const Path& newPath ) = 0;
    virtual void reload( bool keepLineEndingCharacter ) = 0;
    virtual void reload() = 0;
    virtual void load( bool keepLineEndingCharacter, bool removeBottomEmptyLines );
    virtual void loadBackground( bool keepLineEndingCharacter, bool removeBottomEmptyLines, std::function<void( void )> finishCallback );
    virtual void loadFromString( const String& contents, bool keepLineEndingCharacter = false );
    virtual void loadFromStringNoEmptyLines( const String& contents, bool keepLineEndingCharacter = false );
    virtual void unload() = 0;
    virtual bool getIsLoaded() const;

    void getCreationTime(Time& outTime);
    void getLastModificationTime( Time& outTime );

    void toggleCache( bool enabled );
    bool getIsCacheEnabled() const;

    const String& getMD5();
    const String& getSizeBytes() const;
    bool getIsBigFile() const;

    virtual const String& firstLine() const = 0;
    virtual const String& lastLine() const = 0;

    virtual const String& getAsOneString() const = 0;
    virtual const char** getContent() const = 0;

    virtual unsigned getLinesCount() const = 0;

    virtual FileType getType() const = 0;
    const FileList& getChildList() const;
    void addChild( IFile* file );

    bool operator==( const IFile& arg ) const;
    bool operator<( const IFile& arg ) const;
    bool operator>( const IFile& arg ) const;

    virtual ~IFile();

protected:
    bool m_keepLineEndingCharacter{ false };
    bool m_removeBottomEmptyLines{ false };
    CUL::CULInterface* p_cullInterface = nullptr;

private:
    void calculateMD5();
    void calculateSizeBytes();
    void waitForDiskToBeReady();
    FileList m_fileList;
    FS::Path m_path;
    String m_md5;

    Time m_creationTime;
    Time m_lastModificationTime;

    String m_sizeBytes;
    bool m_cacheEnabled{ true };

    void waitForBackgroundLoad();
    std::unique_ptr<ThreadWrapper> m_backgroundLoadThread;
    bool m_loaded{ false };

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
