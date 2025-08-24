#pragma once

#include "CUL/GenericUtils/DelegateTemplate.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/Threading/Worker.hpp"
#include "CUL/Time.hpp"

#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_list.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_future.hpp"
#include <CUL/STL_IMPORTS/STD_map.hpp>

struct sqlite3;

struct ListAndApi;

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

using MD5Value = String;

struct FileInfo
{
    bool Found = false;
    MD5Value MD5;
    String Size;
    Path FilePath;
    Time ModTime;

    bool operator==( const FileInfo& second ) const;
    bool operator<( const FileInfo& second ) const;
};

struct HashGroup
{
    MD5Value MD5;
    std::vector<FileInfo> Files;
};

struct SizeGroup
{
    std::uint64_t Size;
    std::vector<SizeGroup> Sizes;
};

struct SameSizeSameHashGroup
{
    std::uint64_t Size{ 0u };
    MD5Value MD5;
    std::vector<FileInfo> Files;
};

struct MD5List
{
    std::map<MD5Value, std::set<FileInfo>> Files;
};

enum class EOrderType : std::uint8_t
{
    None = 0u,
    Asc,
    Desc
};

class SortedStructuredListOfFiles
{
public:
    SortedStructuredListOfFiles();
    SortedStructuredListOfFiles( const SortedStructuredListOfFiles& rhv );
    SortedStructuredListOfFiles( SortedStructuredListOfFiles&& rhv );
    SortedStructuredListOfFiles& operator=( const SortedStructuredListOfFiles& arg );
    SortedStructuredListOfFiles& operator=( SortedStructuredListOfFiles&& arg );

    void sort();
    void addFile( const FileInfo& arg );
    std::vector<std::int32_t> getPossibleSizes( EOrderType inOrderType ) const;

    MD5List getMd5List( std::uint64_t inSize ) const;

    ~SortedStructuredListOfFiles();

protected:
private:

    mutable std::map<std::uint64_t, MD5List> m_groupsBySize;
};


class CULLib_API FileDatabase final
{
public:


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

    void getListOfPossibleDuplicates( SortedStructuredListOfFiles& inOutPossibleDuplicates );

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