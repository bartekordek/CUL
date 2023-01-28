#pragma once

#include "CUL/GenericUtils/DelegateTemplate.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/Threading/Worker.hpp"

#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_list.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

struct sqlite3;

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

class CULLib_API FileDatabase final
{
public:
    using MD5Value = String;

    struct FileInfo
    {
        MD5Value MD5;
        String Size;
        Path Path;

        bool operator==( const FileInfo& second ) const;
    };

    FileDatabase();
    void loadFilesFromDatabase( const Path& dbPath );
	void addFilesFloadFilesFromDatabaseromDB();

    void addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime );
    void addFileToDb( const Path& path );
    void addFileToDbCache( const FileInfo& path );

    void removeFileFromDB( const CUL::String& path );
    void removeFileFromDBCache( const CUL::String& path );

    std::list<FileInfo>::iterator getNextFile();

    ~FileDatabase();

    CUL::GUTILS::DelegateTemplateOneParam<FileInfo> FoundFileDelegate;

protected:
private:
    void initDb();
    void removeFilesThatDoesNotExist();

    sqlite3* m_db = nullptr;
    Path m_databasePath;

    std::mutex m_filesMtx;
    std::list<FileInfo> m_files;

    String m_currentFile;

    std::list<FileInfo>::iterator m_currentFilePath;

private:
    FileDatabase( const FileDatabase& rhv ) = delete;
    FileDatabase( const FileDatabase&& rhv ) = delete;
    FileDatabase& operator=( const FileDatabase& rhv ) = delete;
    FileDatabase& operator=( FileDatabase&& rhv ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )