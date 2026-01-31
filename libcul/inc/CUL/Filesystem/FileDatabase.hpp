#pragma once

#include "CUL/GenericUtils/DelegateTemplate.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/Threading/Worker.hpp"
#include "CUL/Threading/ThreadWrap.hpp"
#include "CUL/Time.hpp"

#include "CUL/STL_IMPORTS/STD_atomic.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_list.hpp"
#include "CUL/STL_IMPORTS/STD_optional.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_future.hpp"
#include <CUL/STL_IMPORTS/STD_map.hpp>

struct sqlite3;

struct ListAndApi;

NAMESPACE_BEGIN( CUL )

class TaskCallback;

NAMESPACE_BEGIN( FS )

using Str = STDStringWrapper;
using MD5Value = Str;


struct FileInfo
{
    bool Found = false;
    MD5Value MD5;
    Str Size;
    Str FilePath;
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

enum class ELockType : std::uint8_t
{
    Locked,
    Unlocked
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

struct CacheUsage
{
    float Percentage{ 0.f };
    std::uint64_t Curr{ 0u };
    std::uint64_t Max{ 0u };
    float MBUsed{ 0.f };
};

class CULLib_API FileDatabase final
{
public:
    FileDatabase();
    void loadFilesFromDatabase( const Path& dbPath );
    void loadFilesFromDatabase();

    void addFile( MD5Value md5, const CUL::StringWr& filePath, const CUL::StringWr& fileSize, const CUL::StringWr& modTime );

    void removeFileFromDB( const CUL::StringWr& path );
    void removeFilesFromDb( const std::vector<CUL::StringWr>& paths );

    std::optional<FileInfo> getFileInfo( const CUL::StringWr& path ) const;
    float getPercentage() const;

    void getListOfSizes( std::vector<uint64_t>& out ) const;
    std::vector<CUL::StringWr> getListOfMd5() const;
    std::vector<CUL::StringWr> getListOfMd5( std::uint64_t inSize ) const;
    void getFiles( uint64_t size, const CUL::StringWr& md5, std::vector<FileInfo>& out ) const;
    void getFiles( uint64_t size, std::vector<FileInfo>& out ) const;

    void getFilesMatching( const CUL::StringWr& fileSize, const CUL::StringWr& md5, std::list<CUL::StringWr>& out ) const;
    CacheUsage getCacheUsage() const;

    void getListOfPossibleDuplicates( SortedStructuredListOfFiles& inOutPossibleDuplicates );

    ~FileDatabase();

protected:
private:
    void initDb();
    void waitForInit() const;
    bool m_initialized = false;
    int64_t getFileCount() const;
    void updateCache();
    void getFilesFromDB( uint64_t size, const CUL::StringWr& md5, std::vector<FileInfo>& out ) const;
    void getFilesFromDB( uint64_t size, std::vector<FileInfo>& out ) const;

    void getListOfSizesFromDb( std::vector<uint64_t>& out ) const;
    std::optional<FileInfo> getFromCache( const StringWr& inFilePath ) const;
    bool removeFromCache( const StringWr& inFilePath );
    void addFileImpl( ELockType inLockType, MD5Value md5, const CUL::StringWr& filePath, const CUL::StringWr& fileSize, const CUL::StringWr& modTime );
    void removeFileFromDB_Impl( const CUL::StringWr& path );
    void addToCache( const FileInfo& inFile );
    std::optional<FileInfo> getFileInfo_Impl( ELockType inLockType, const CUL::StringWr& path ) const;

    static StringWr sanitize( const StringWr& inString );
    static StringWr deSanitize( const StringWr& inString );
    bool getIsFull() const;
    void fetchUsage();

    sqlite3* m_db = nullptr;
    Path m_databasePath = "FilesList.db";

    StringWr m_currentFile;
    std::atomic<int64_t> m_current = 0;
    std::atomic<int64_t> m_rowCount = 0;

    std::future<bool> m_deleteRemnantsDone;
    ListAndApi* m_fetchList = nullptr;
    std::mutex m_fetchListMtx;

    std::list<FileInfo> m_cachedFiles;
    std::size_t m_cachedFilesMax{ 0u };
    mutable std::mutex m_cachedFilesMtx;

    CUL::ThreadWrapper m_cachedFileInserting;
    bool m_update{ true };
    void updateFunction();

    std::atomic<std::uint32_t> m_tasksCounter;

    CUL::TaskCallback* m_updateCache{ nullptr };

    CacheUsage m_usage;

private:
    FileDatabase( const FileDatabase& rhv ) = delete;
    FileDatabase( const FileDatabase&& rhv ) = delete;
    FileDatabase& operator=( const FileDatabase& rhv ) = delete;
    FileDatabase& operator=( FileDatabase&& rhv ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )