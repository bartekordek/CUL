#pragma once

#include "CUL/GenericUtils/DelegateTemplate.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/Threading/Worker.hpp"

#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_list.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_future.hpp"

struct sqlite3;

struct ListAndApi;

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )



class CULLib_API FileDatabase final
{
public:
    using MD5Value = String;

    struct FileInfo
    {
        bool Found = false;
        MD5Value MD5;
        String Size;
        Path FilePath;
        String ModTime;

        bool operator==( const FileInfo& second ) const;
    };

    FileDatabase();
    void loadFilesFromDatabase( const Path& dbPath );
    void loadFilesFromDatabase();

    void addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime );

    void removeFileFromDB( const CUL::String& path );
    void removeFilesFromDb( const std::vector<CUL::String>& paths );

    FileInfo getFileInfo( const CUL::String& path ) const;
    float getPercentage() const;

    CUL::String getDbState() const;
    std::vector<uint64_t> getListOfSizes() const;
    std::vector<CUL::String> getListOfMd5() const;
    std::vector<FileInfo> getFiles( uint64_t size, const CUL::String& md5 ) const;
    std::vector<FileInfo> getFiles( uint64_t size ) const;

    std::list<CUL::String> getFilesMatching( const CUL::String& fileSize, const CUL::String& md5 ) const;

    ~FileDatabase();

protected:
private:
    void initDb();
    int64_t getFileCount() const;
    static String sanitize( const String& inString );
    static String deSanitize( const String& inString );
    void setDBstate( const CUL::String& state );
    bool deleteRemnants();

    sqlite3* m_db = nullptr;
    Path m_databasePath = "FilesList.db";

    String m_currentFile;
    std::atomic<int64_t> m_current = 0;
    std::atomic<int64_t> m_rowCount = 0;

    mutable std::mutex m_dbStateMtx;
    CUL::String m_dbState = "Uninitialized";

    std::future<bool> m_deleteRemnantsDone;
    ListAndApi* m_fetchList = nullptr;

private:
    FileDatabase( const FileDatabase& rhv ) = delete;
    FileDatabase( const FileDatabase&& rhv ) = delete;
    FileDatabase& operator=( const FileDatabase& rhv ) = delete;
    FileDatabase& operator=( FileDatabase&& rhv ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )