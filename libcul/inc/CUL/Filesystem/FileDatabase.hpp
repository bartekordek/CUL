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

using MD5Value = String;

class CULLib_API FileDatabase final
{
public:
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

    void getListOfSizes( std::vector<uint64_t>& out ) const;
    std::vector<CUL::String> getListOfMd5() const;
    void getFiles( uint64_t size, const CUL::String& md5, std::vector<FileInfo>& out ) const;
    void getFiles( uint64_t size, std::vector<FileInfo>& out ) const;

    void getFilesMatching( const CUL::String& fileSize, const CUL::String& md5, std::list<CUL::String>& out ) const;
    bool deleteRemnants();

    ~FileDatabase();

protected:
private:
    void initDb();
    void waitForInit()const;
    bool m_initialized = false;
    int64_t getFileCount() const;
    static String sanitize( const String& inString );
    static String deSanitize( const String& inString );

    sqlite3* m_db = nullptr;
    Path m_databasePath = "FilesList.db";

    String m_currentFile;
    std::atomic<int64_t> m_current = 0;
    std::atomic<int64_t> m_rowCount = 0;

    std::future<bool> m_deleteRemnantsDone;
    ListAndApi* m_fetchList = nullptr;
    std::mutex m_fetchListMtx;

private:
    FileDatabase( const FileDatabase& rhv ) = delete;
    FileDatabase( const FileDatabase&& rhv ) = delete;
    FileDatabase& operator=( const FileDatabase& rhv ) = delete;
    FileDatabase& operator=( FileDatabase&& rhv ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )