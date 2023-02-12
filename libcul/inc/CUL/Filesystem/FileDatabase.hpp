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
        Path FilePath;
        String ModTime;

        bool operator==( const FileInfo& second ) const;
    };

    FileDatabase();
    std::vector<String> loadFilesFromDatabase( const Path& dbPath );
    std::vector<String> loadFilesFromDatabase();

    void addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime );

    void removeFileFromDB( const CUL::String& path );

    FileInfo getFileInfo( const CUL::String& path ) const;
    float getPercentage() const;

    CUL::String getDbState() const;

    ~FileDatabase();

protected:
private:
    void initDb();
    int64_t getFileCount() const;
    static String sanitize( const String& inString );
    static String deSanitize( const String& inString );
    void setDBstate( const CUL::String& state );

    sqlite3* m_db = nullptr;
    Path m_databasePath = "FilesList.db";

    String m_currentFile;
    std::atomic<int64_t> m_current = 0;
    std::atomic<int64_t> m_rowCount = 0;

    mutable std::mutex m_dbStateMtx;
    CUL::String m_dbState = "Uninitialized";

private:
    FileDatabase( const FileDatabase& rhv ) = delete;
    FileDatabase( const FileDatabase&& rhv ) = delete;
    FileDatabase& operator=( const FileDatabase& rhv ) = delete;
    FileDatabase& operator=( FileDatabase&& rhv ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )