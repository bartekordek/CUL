#include "CUL/Filesystem/FileDatabase.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/ITimer.hpp"
#include "Filesystem/FSUtils.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/Threading/MultiWorkerSystem.hpp"
#include "CUL/Threading/TaskCallback.hpp"
#include "CUL/Threading/ThreadUtil.hpp"

#include "Imports/IMPORT_sqlite3.hpp"
#include "CUL/Proifling/Profiler.hpp"
#include "CUL/String/StringUtil.hpp"
#include "CUL/STL_IMPORTS/STD_inttypes.hpp"

#ifdef _MSC_VER
    #pragma warning( push, 0 )
    #pragma warning( disable : 1404 )
#endif

#define USE_CACHE 1

using namespace CUL;
using namespace FS;

#if 0  // DEBUG_THIS_FILE
    #define DEBUG_THIS_FILE 1

    #if defined( CUL_COMPILER_MSVC )
        #pragma optimize( "", off )
    #elif defined( CUL_COMPILER_CLANG )
        #pragma clang optimize off
    #elif defined( CUL_COMPILER_GCC )
        #pragma GCC push_options
        #pragma GCC optimize( "O0" )
    #endif
#endif

#if defined( SQLITE_THREADSAFE ) && SQLITE_THREADSAFE == 1
    #pragma message( "CUL SQLITE_THREADSAFE ENABLED." )
    #define DO_NO_USE_SQLITE_MTX 0
#else  // #if defined( SQLITE_THREADSAFE ) && SQLITE_THREADSAFE == 1
    #pragma message( "CUL SQLITE_THREADSAFE DISABLED." )
    #define DO_NO_USE_SQLITE_MTX 1
#endif  // #if defined( SQLITE_THREADSAFE ) && SQLITE_THREADSAFE == 1

#if DO_NO_USE_SQLITE_MTX
std::mutex g_sqliteMtx;
#else
#endif  // DO_NO_USE_SQLITE_MTX

static FileDatabase* g_dbInstance = nullptr;

std::int32_t SQLiteQueryImpl( sqlite3* db, const char* query, int ( *callback )( void*, int, char**, char** ), void* firstArgument,
                              char** errmsg )
{
    ProfilerScope( "SQLiteQueryImpl" );
    std::int32_t rc = sqlite3_exec( db, query, callback, firstArgument, errmsg );
    return rc;
}

std::int32_t SQLiteQuery( sqlite3* db, const char* query, int ( *callback )( void*, int, char**, char** ), void* firstArgument,
                          char** errmsg )
{
    ProfilerScopeColor( "SQLiteQuery", 16711680 );
#if DO_NO_USE_SQLITE_MTX
    g_sqliteMtx.lock();
#endif  // DO_NO_USE_SQLITE_MTX
    std::int32_t rc = SQLiteQueryImpl( db, query, callback, firstArgument, errmsg );
#if DO_NO_USE_SQLITE_MTX
    g_sqliteMtx.unlock();
#endif  // DO_NO_USE_SQLITE_MTX
    return rc;
}

void EscapeCharacters( StringWr& inOutString )
{
    inOutString.replace( "\\", "\\\\" );
}

bool FileInfo::operator==( const FileInfo& second ) const
{
    return FilePath == second.FilePath;
}

bool FileInfo::operator<( const FileInfo& second ) const
{
    return FilePath < second.FilePath;
}

FileDatabase::FileDatabase(): m_cachedFilesMax( 256u * 1024u * 1024u )
{
    m_cachedFileInserting.setBody(
        [this]()
        {
            updateFunction();
        } );
}

void FileDatabase::updateFunction()
{
    while( m_update )
    {
        // CUL::ITimer::sleepMiliSeconds( 2000 );
        //{
        //     std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
        //     std::size_t currentSize = m_cachedFiles.size();
        //     while( currentSize >= m_cachedFilesMax )
        //     {
        //         m_cachedFiles.pop_back();
        //         currentSize = m_cachedFiles.size();
        //     }
        // }
    }
}

void FileDatabase::loadFilesFromDatabase( const Path& inPath )
{
    m_databasePath = inPath;
    loadFilesFromDatabase();
}

struct ListAndApi
{
    FileDatabase* thisPtr = nullptr;
    std::vector<StringWr> FilesList{};
    std::deque<StringWr> RemoveList{};
    std::mutex RemoveListMtx;
    FSApi* FS_API = nullptr;
    std::atomic<int64_t>* m_currentFileIndex = nullptr;
    std::vector<FileInfo> Files;
};

float FileDatabase::getPercentage() const
{
    return 100.f * m_current / ( 1.f * m_rowCount );
}

void FileDatabase::getListOfPossibleDuplicates( SortedStructuredListOfFiles& inOutPossibleDuplicates )
{
    ProfilerScope( "FileDatabase::getListOfPossibleDuplicates" );

    const char* query =
        "SELECT A.*FROM FILES A\n"
        "INNER JOIN (SELECT SIZE, MD5\n"
        "FROM FILES\n"
        "GROUP BY SIZE, MD5\n"
        "HAVING COUNT(*) > 1) B\n"
        "ON A.SIZE = B.SIZE AND A.MD5 = B.MD5 ORDER BY SIZE;";

    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        auto resulPtr = reinterpret_cast<SortedStructuredListOfFiles*>( voidPtr );

        Str filePath( argv[0] );
        const std::string size = argv[1];
        const std::string md5 = argv[2];
        const std::string lastMod = argv[3];
        FileInfo fi;
        fi.FilePath = filePath;
        StringWr pathCopy = fi.FilePath.getValue();
        if( pathCopy.empty() == false )
        {
            fi.FilePath = pathCopy;
        }

        fi.MD5 = md5;
        fi.ModTime.fromString( lastMod );
        fi.Size = size;

        resulPtr->addFile( fi );

        return 0;
    };

    char* zErrMsg = nullptr;

    std::int32_t rc = SQLiteQuery( m_db, query, callback, &inOutPossibleDuplicates, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        Assert::check( false, "DB ERROR: %s", zErrMsg );
    }
}

void FileDatabase::getListOfSizes( std::vector<uint64_t>& out ) const
{
    ProfilerScope( "FileDatabase::getListOfSizes" );

#if USE_CACHE
    std::set<uint64_t> sizes;
    {
        std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
        for( const auto& fi : m_cachedFiles )
        {
            sizes.insert( fi.first );
        }
    }
    {
        for( std::uint64_t currIn : sizes )
        {
            out.push_back( currIn );
        }

        std::sort( out.begin(), out.end(), std::greater<>() );
    }
#else   // USE_CACHE
    getListOfSizes( out );
#endif  // USE_CACHE
}

void FileDatabase::getListOfSizesFromDb( std::vector<uint64_t>& out ) const
{
    const std::string sqlQuery = std::string( "SELECT DISTINCT SIZE FROM FILES ORDER BY SIZE;" );
    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        StringWr valueAsString = argv[0];
        std::vector<uint64_t>* resulPtr = reinterpret_cast<std::vector<uint64_t>*>( voidPtr );
        resulPtr->push_back( valueAsString.toUint64() );

        return 0;
    };

    char* zErrMsg = nullptr;
    const std::int32_t rc = SQLiteQuery( m_db, sqlQuery.c_str(), callback, &out, &zErrMsg );

    if( ( rc != SQLITE_OK ) && ( rc != SQLITE_MISUSE ) )
    {
        if( StringUtil::cmp( zErrMsg, "no such table" ) != 0 )  // new database.
        {
            Assert::check( false, "DB ERROR: %s", zErrMsg );
        }
    }
}

std::vector<StringWr> FileDatabase::getListOfMd5() const
{
    ProfilerScope( "FileDatabase::getListOfMd5 void" );
    std::vector<StringWr> result;
#if USE_CACHE
    std::set<MD5Value> md5s;
    {
        std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
        for( const auto& fi : m_cachedFiles )
        {
            for( const auto& md5 : fi.second )
            {
                md5s.insert( md5.first );
            }
        }
    }
    {
        for( const MD5Value& md5 : md5s )
        {
            result.push_back( md5.getValue() );
        }
    }

#else   // #if USE_CACHE
    const std::string sqlQuery = std::string( "SELECT DISTINCT MD5 FROM FILES ORDER BY SIZE;" );
    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        StringWr valueAsString = argv[0];
        std::vector<StringWr>* resulPtr = reinterpret_cast<std::vector<StringWr>*>( voidPtr );
        resulPtr->push_back( valueAsString );

        return 0;
    };

    char* zErrMsg = nullptr;
    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.c_str(), callback, &result, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        Assert::check( false, "DB ERROR: %s", zErrMsg );
    }
#endif  // #if USE_CACHE
    return result;
}

std::vector<StringWr> FileDatabase::getListOfMd5( std::uint64_t inSize ) const
{
    ProfilerScope( "FileDatabase::getListOfMd5 inSize" );
    std::vector<StringWr> result;
#if USE_CACHE
    std::set<MD5Value> md5s;
    {
        std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
        const auto it = m_cachedFiles.find( inSize );
        if( it != m_cachedFiles.end() )
        {
            for( const auto& md5List : it->second )
            {
                md5s.insert( md5List.first );
            }
        }
    }
    {
        for( const MD5Value& md5 : md5s )
        {
            result.push_back( md5.getValue() );
        }
    }
#else   // #if USE_CACHE
    std::vector<std::string> tmp;
    constexpr std::size_t defaultSize{ 1024u * 1024u };
    {
        ProfilerScope( "FileDatabase::getListOfMd5 reserve" );
        tmp.reserve( defaultSize );
    }

    constexpr std::size_t bufferLength = 1024u;
    char buffer[bufferLength];
    snprintf( buffer, bufferLength, "SELECT DISTINCT MD5 FROM FILES WHERE SIZE=\"%I64u\";", inSize );

    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        ProfilerScope( "FileDatabase::getListOfMd5 inSize it" );
        std::string valueAsString = argv[0];
        std::vector<std::string>* resulPtr = reinterpret_cast<std::vector<std::string>*>( voidPtr );
        resulPtr->push_back( valueAsString );

        return 0;
    };

    char* zErrMsg = nullptr;
    std::int32_t rc = SQLiteQuery( m_db, buffer, callback, &tmp, &zErrMsg );

    if( result.empty() == false )
    {
        result.reserve( result.size() );
        for( const std::string& currentString : tmp )
        {
            result.push_back( currentString );
        }
    }

    if( rc != SQLITE_OK )
    {
        Assert::check( false, "DB ERROR: %s", zErrMsg );
    }
#endif  // #if USE_CACHE
    return result;
}

void FileDatabase::getFiles( uint64_t inSize, const StringWr& md5, std::vector<FileInfo>& out ) const
{
#if USE_CACHE
    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
    const auto it = m_cachedFiles.find( inSize );
    if( it != m_cachedFiles.end() )
    {
        const auto itMd5 = it->second.find( md5.getSTDString() );
        if( itMd5 != it->second.end() )
        {
            for( const auto& itFile : itMd5->second.Files )
            {
                out.push_back( itFile );
            }
        }
    }
#else
    getFilesFromDB( size, md5, out );
#endif
}

void FileDatabase::getFilesFromDB( uint64_t size, const StringWr& md5, std::vector<FileInfo>& out ) const
{
    ProfilerScope( "FileDatabase::getFiles" );
    const StringWr sqlQuery = StringWr::createFromPrintf(
        "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES WHERE SIZE=\"%d\" AND MD5=\"%s\"", size, md5.getUtfChar() );
    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        std::string filePath( argv[0] );
        const std::string size = argv[1];
        const std::string md5 = argv[2];
        const StringWr lastMod = argv[3];
        auto resulPtr = reinterpret_cast<std::vector<FileInfo>*>( voidPtr );
        FileInfo fi;
        fi.FilePath = filePath;
        StringWr pathCopy = fi.FilePath.getValue();
        if( pathCopy.empty() == false )
        {
            fi.FilePath = pathCopy;
        }

        fi.MD5 = md5;
        fi.ModTime.fromString( lastMod );
        fi.Size = size;
        resulPtr->push_back( fi );

        return 0;
    };

    char* zErrMsg = nullptr;
    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.getUtfChar(), callback, &out, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::check( false, "DB ERROR: %s", zErrMsg );
    }
}

void FileDatabase::getFiles( uint64_t inSize, std::vector<FileInfo>& out ) const
{
#if USE_CACHE
    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
    out.reserve( m_cachedFiles.size() );

    const auto it = m_cachedFiles.find( inSize );
    if( it != m_cachedFiles.end() )
    {
        for( const auto& md5Pair : it->second )
        {
            for( const auto& filePair : md5Pair.second.Files )
            {
                out.push_back( filePair );
            }
        }
    }
#else
    getFilesFromDb( size, out );
#endif
}

void FileDatabase::getFilesFromDB( uint64_t size, std::vector<FileInfo>& out ) const
{
    ProfilerScope( "FileDatabase::getFiles" );

    const StringWr sqlQuery = StringWr::createFromPrintf( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES WHERE SIZE=\"%d\";", size );
    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        auto resulPtr = reinterpret_cast<std::vector<FileInfo>*>( voidPtr );

        Time modTime;
        modTime.fromString( argv[3] );
        resulPtr->emplace_back( FileInfo{ false, argv[2], argv[1], argv[0], modTime } );

        return 0;
    };

    char* zErrMsg = nullptr;
    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.getUtfChar(), callback, &out, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        Assert::check( false, "DB ERROR: %s", zErrMsg );
    }
}

void FileDatabase::loadFilesFromDatabase()
{
    ProfilerScope( "FileDatabase::loadFilesFromDatabase" );

    ThreadUtil::getInstance().setThreadStatus( "FileDatabase::loadFilesFromDatabase::initDb();" );
    initDb();

    std::lock_guard<std::mutex> locker( m_fetchListMtx );
    m_fetchList = new ListAndApi();

    m_fetchList->thisPtr = this;
    m_fetchList->FS_API = CUL::CULInterface::getInstance()->getFS();
    m_fetchList->m_currentFileIndex = &m_current;
}

void FileDatabase::getFilesMatching( const StringWr& fileSize, const StringWr& md5, std::list<StringWr>& out ) const
{
    ProfilerScope( "FileDatabase::getFilesMatching" );

    const StringWr sqlQuery =
        StringWr::createFromPrintf( "SELECT PATH FROM FILES WHERE ( SIZE='%d' AND MD5='%s');", fileSize, md5.getUtfChar() );

    char* zErrMsg = nullptr;
    auto callback = []( void* voidValue, int argc, char** argv, char** info )
    {
        std::list<StringWr>* resultPtr = reinterpret_cast<std::list<StringWr>*>( voidValue );
        StringWr foundPath( argv[0] );
        resultPtr->push_back( foundPath );
        return 0;
    };

    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.getUtfChar(), callback, &out, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::simple( false, "DB ERROR!" );
    }
}

CacheUsage FileDatabase::getCacheUsage() const
{
    return m_usage;
}

int64_t FileDatabase::getFileCount() const
{
    ProfilerScope( "FileDatabase::getFileCount" );

    int64_t result = 0;

    char* zErrMsg = nullptr;
    // std::string sqlQuery = std::string( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES" );
    std::string sqlQuery = std::string( "SELECT COUNT(PATH) as something from FILES" );
    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        StringWr valueAsString = argv[0];
        auto resulPtr = reinterpret_cast<int64_t*>( voidPtr );
        *resulPtr = valueAsString.toInt64();

        return 0;
    };

    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.c_str(), callback, &result, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        Assert::check( false, "DB ERROR: %s", zErrMsg );
    }

    return result;
}

std::optional<FileInfo> FileDatabase::getFromCache( const StringWr& inFilePath ) const
{
    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );

    for( const auto& sizePair : m_cachedFiles )
    {
        for( const auto& md5Pair : sizePair.second )
        {
            const auto it = std::find_if( md5Pair.second.Files.begin(), md5Pair.second.Files.end(),
                                          [&inFilePath]( const FileInfo& curr )
                                          {
                                              return curr.FilePath.equals( inFilePath );
                                          } );
            if( it != md5Pair.second.Files.end() )
            {
                return *it;
            }
        }
    }

    return {};
}

bool FileDatabase::removeFromCache( const StringWr& inFilePath )
{
    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );

    for( auto& sizePair : m_cachedFiles )
    {
        for( auto& md5Pair : sizePair.second )
        {
            auto it = std::find_if( md5Pair.second.Files.begin(), md5Pair.second.Files.end(),
                                    [&inFilePath]( const FileInfo& curr )
                                    {
                                        return curr.FilePath.equals( inFilePath );
                                    } );
            if( it != md5Pair.second.Files.end() )
            {
                md5Pair.second.Files.erase( it );
                fetchUsage();
                return true;
            }
        }
    }

    return false;
}

void FileDatabase::addToCache( const std::vector<FileInfo>& inFiles ) const
{
    ProfileScopeVar( FileDatabase_addToCache_many );
    if( getIsFull() )
    {
        ProfileScopeVar( FileDatabase_addToCache_waitForEmpty );
        while( getIsFull() )
        {
            ITimer::sleepMicroSeconds( 1 );
        }
    }

    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
    ProfileScopeVar( FileDatabase_addToCache_outOfMtx );

    for( const FileInfo& file : inFiles )
    {
        std::unordered_map<std::string, HashGroup>& md5Group = m_cachedFiles[file.Size.toInt64()];
        auto& fileGroup = md5Group[file.MD5.getSTDString()];
        fileGroup.Files.insert( file );
    }
    fetchUsage();
}

void FileDatabase::addToCache( const FileInfo& inFile ) const
{
    ProfileScopeVar( FileDatabase_addToCache );
    if( getIsFull() )
    {
        ProfileScopeVar( FileDatabase_addToCache_waitForEmpty );
        while( getIsFull() )
        {
            ITimer::sleepMicroSeconds( 1 );
        }
    }

    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
    ProfileScopeVar( FileDatabase_addToCache_outOfMtx );

    std::unordered_map<std::string, HashGroup>& md5Group = m_cachedFiles[inFile.Size.toInt64()];
    auto& fileGroup = md5Group[inFile.MD5.getSTDString()];
    fileGroup.Files.insert( inFile );
    fetchUsage();
}

void FileDatabase::fetchUsage() const
{
    // m_cachedFilesMtx
    ProfilerScope( "FileDatabase::fetchUsage" );
    m_usage.Curr = static_cast<decltype( m_usage.Curr )>( m_cachedFiles.size() );
    m_usage.Max = static_cast<decltype( m_usage.Max )>( m_cachedFilesMax );

    constexpr static std::size_t sizeOfOne = sizeof( FileInfo );
    m_usage.MBUsed = m_usage.Curr * sizeOfOne;  // How many Bytes.
    m_usage.MBUsed /= 1024.f;                   // How many KiloBytes.
    m_usage.MBUsed /= 1024.f;                   // How many MegaBytes.

    m_usage.Percentage = static_cast<float>( m_usage.Curr ) / static_cast<float>( m_usage.Max );
}

bool FileDatabase::getIsFull() const
{
    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
    return m_cachedFiles.size() >= m_cachedFilesMax;
}

void FileDatabase::initDb()
{
    constexpr std::size_t sizeOfWchar = sizeof( wchar_t );

    ProfilerScope( "FileDatabase::initDb" );
    ThreadUtil::getInstance().setThreadStatus( "Initi db..." );
    int rc = sqlite3_open( m_databasePath.getPath().getUtfChar(), &m_db );

    constexpr std::size_t bufferLength = 4096u;
    char sqlQueryBuffor[bufferLength];
    snprintf( sqlQueryBuffor, bufferLength, "SELECT * FROM FILES" );

    auto callback = []( void*, int, char**, char** )
    {
        // DuplicateFinder::s_instance->callback(NotUsed, argc, argv, azColName);
        return 0;
    };

    char* zErrMsg = nullptr;
    rc = SQLiteQuery( m_db, sqlQueryBuffor, nullptr, 0, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        const std::size_t writeSize = snprintf( sqlQueryBuffor, bufferLength,
                                                "CREATE TABLE FILES (\
        PATH BINARY(2048),\
        SIZE BIGINT(255),\
        MD5 varchar(1024),\
        LAST_MODIFICATION varchar(1024),\
        CONSTRAINT DB_ID PRIMARY KEY (PATH) \
        );" );
        Assert::simple( ( writeSize < bufferLength ) && ( writeSize > 0 ), "Query input wrong! Command is too long!" );

        std::string errorResult( zErrMsg );
        rc = sqlite3_exec( m_db, sqlQueryBuffor, callback, 0, &zErrMsg );
        if( rc != SQLITE_OK )
        {
            Assert::simple( false, "DB ERROR!" );
        }
    }

    m_cachedFileInserting.run();

    m_updateCache = new CUL::TaskCallback();
    m_updateCache->Type = ITask::EType::Loop;
    m_updateCache->Priority = EPriority::High;
    m_updateCache->Callback = [this]( int8_t workerId )
    {
        ProfilerScope( "FileDatabase::updateCache LAMBDA" );
        updateCache();
    };

    MultiWorkerSystem::getInstance().registerTask( m_updateCache );

    ThreadUtil::getInstance().setThreadStatus( "Init db... done." );
    m_initialized = true;
}

struct DataS
{
    std::vector<FileInfo> Files;
    std::uint64_t Counter{ 0u };
    std::uint64_t Max{ 0u };
    std::size_t bufferLength{ 1024u };
    char buffer[1024];
};

void FileDatabase::updateCache()
{
    ProfilerScopeColor( "FileDatabase::updateCache", 0xFF0000FF );
    std::vector<uint64_t> listOfSizes;
    getListOfSizesFromDb( listOfSizes );
    const std::int64_t listOfSizesSize = static_cast<std::int64_t>( listOfSizes.size() );
    std::vector<CUL::FS::FileInfo> sameSizeFiles;
    std::vector<CUL::FS::FileInfo> filesToAdd;
    for( std::int64_t i = listOfSizesSize - 1; i >= 0; --i )
    {
        ProfilerScope( "FileDatabase::updateCache it 1" );
        const auto size = listOfSizes[i];
        getFilesFromDB( size, sameSizeFiles );
        for( const CUL::FS::FileInfo& fi : sameSizeFiles )
        {
            filesToAdd.push_back( fi );
        }
        sameSizeFiles.clear();
    }
    addToCache( filesToAdd );
}

void FileDatabase::addFile( MD5Value md5, const StringWr& filePath, const StringWr& fileSize, const StringWr& modTime )
{
    ProfilerScope( "FileDatabase::addFile" );
    ++m_tasksCounter;
    auto resultToBeDiscarded = std::async( std::launch::async,
                                           [this, md5, filePath, fileSize, modTime]()
                                           {
                                               FileInfo fi;
                                               fi.MD5 = md5;
                                               fi.FilePath = filePath;
                                               fi.Size = fileSize;
                                               fi.ModTime.fromString( modTime );
                                               fi.Found = true;

                                               addToCache( fi );

                                               addFileImpl( ELockType::Locked, md5, filePath, fileSize, modTime );
                                               --m_tasksCounter;
                                           } );
}

void FileDatabase::addFileImpl( ELockType inLockType, MD5Value md5, const StringWr& filePath, const StringWr& fileSize,
                                const StringWr& modTime )
{
    ProfilerScope( "FileDatabase::addFile" );

    StringWr filePathNormalized = filePath;
    std::optional<FileInfo> foundFile = getFileInfo_Impl( inLockType, filePath );
    char* zErrMsg = nullptr;
    auto callback = []( void*, int, char**, char** )
    {
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    StringWr sqlQuery = "";

    constexpr std::size_t bufferLength = 1024u;
    char buffer[bufferLength];
    if( foundFile )
    {
        const std::string binaryForm = filePathNormalized.getUtfChar();
        snprintf( buffer, bufferLength, "UPDATE FILES SET SIZE='%s', MD5='%s', LAST_MODIFICATION='%s' WHERE PATH=\"%s\"",
                  fileSize.getUtfChar(), md5.getSTDString().c_str(), modTime.getUtfChar(), binaryForm.c_str() );
    }
    else
    {
        const std::string binaryValue = filePathNormalized.getUtfChar();

        snprintf( buffer, bufferLength, "INSERT INTO FILES (PATH, SIZE, MD5, LAST_MODIFICATION ) VALUES ( \"%s\", '%s', '%s', '%s' );",
                  binaryValue.c_str(), fileSize.getUtfChar(), md5.getSTDString().c_str(), modTime.getUtfChar() );
    }
    sqlQuery = buffer;

    std::int32_t rc{ 0 };

    if( inLockType == ELockType::Locked )
    {
        rc = SQLiteQuery( m_db, sqlQuery.getUtfChar(), callback, nullptr, &zErrMsg );
    }
    else
    {
        rc = SQLiteQueryImpl( m_db, sqlQuery.getUtfChar(), callback, nullptr, &zErrMsg );
    }

    if( rc != SQLITE_OK )
    {
        std::string errMessage = zErrMsg;
        if( errMessage.find( "no such table" ) != std::string::npos )
        {
            // OK, table does not exist yet.
            initDb();
        }
        else
        {
            Assert::simple( false, "DB ERROR!" );
        }
    }
}

std::optional<FileInfo> FileDatabase::getFileInfo( const StringWr& path ) const
{
    ProfilerScope( "FileDatabase::getFileInfo" );
    std::optional<FileInfo> fromCache = getFromCache( path.getValue() );
    if( fromCache )
    {
        return fromCache.value();
    }

    return getFileInfo_Impl( ELockType::Locked, path );
}

std::optional<FileInfo> FileDatabase::getFileInfo_Impl( ELockType inLockType, const StringWr& path ) const
{
    ProfilerScope( "FileDatabase::getFileInfo" );
    std::optional<FileInfo> result;

    waitForInit();
    const StringWr sqlQuery = StringWr::createFromPrintf( "SELECT * FROM FILES WHERE PATH=\"%s\";", path.getUtfChar() );

    auto callback = []( void* fileInfoPtr, int argc, char** argv, char** info )
    {
        ProfilerScope( "FileDatabase::getFileInfo::lambda" );
        std::optional<FileInfo>* fileInfoFromPtr = reinterpret_cast<std::optional<FileInfo>*>( fileInfoPtr );
        FileInfo fi;
        fi.Found = true;
        fi.Size = argv[1];
        fi.MD5 = argv[2];
        fi.ModTime.fromString( argv[3] );

        *fileInfoFromPtr = fi;
        return 0;
    };

    char* zErrMsg = nullptr;

    std::int32_t rc{ 0 };
    if( inLockType == ELockType::Locked )
    {
        rc = SQLiteQuery( m_db, sqlQuery.getUtfChar(), callback, &result, &zErrMsg );
    }
    else
    {
        rc = SQLiteQueryImpl( m_db, sqlQuery.getUtfChar(), callback, &result, &zErrMsg );
    }

    if( result )
    {
        result->FilePath = path;
    }

    constexpr bool PrintInfo = false;
    if( PrintInfo && !result )
    {
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "[FileDatabase::getFileInfo] Could not find: %s", path.getUtfChar() );
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "[FileDatabase::getFileInfo] Used SQL command: %s",
                                                 sqlQuery.getUtfChar() );
    }

    if( rc != SQLITE_OK )
    {
        Assert::check( false, "DB ERROR: %s", zErrMsg );
    }

    if( result )
    {
        addToCache( *result );
    }

    return result;
}

void FileDatabase::waitForInit() const
{
    ProfilerScope( "FileDatabase::waitForInit" );

    if( m_initialized == true )
    {
        return;
    }

    while( m_initialized == false )
    {
        ITimer::sleepMicroSeconds( 1 );
    }
}

void FileDatabase::removeFileFromDB( const StringWr& pathRaw )
{
    ProfilerScope( "FileDatabase::removeFileFromDB" );
    removeFromCache( pathRaw.getValue() );
    removeFileFromDB_Impl( pathRaw );
}

void FileDatabase::removeFileFromDB_Impl( const StringWr& pathRaw )
{
    ProfilerScope( "FileDatabase::removeFileFromDB" );

    ThreadString info = "FileDatabase::removeFileFromDB: " + pathRaw.getSTDString();
    ThreadUtil::getInstance().setThreadStatus( info );

    constexpr std::size_t bufferSize{ 512 };
    static char buffer[bufferSize];
    snprintf( buffer, bufferSize, "FileDatabase::removeFileFromDB pathRaw: %s", pathRaw.getUtfChar() );
    ThreadUtil::getInstance().setThreadStatus( buffer );
    StringWr path = pathRaw;

    const std::string binaryForm = path.getUtfChar();
    std::string sqlQuery = std::string( "DELETE FROM FILES WHERE PATH='" ) + binaryForm + "';";

    char* zErrMsg = nullptr;
    auto callback = []( void* thisPtrValue, int argc, char** argv, char** info )
    {
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.c_str(), callback, nullptr, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        Assert::simple( false, "DB ERROR!" );
    }
}

void FileDatabase::removeFilesFromDb( const std::vector<StringWr>& paths )
{
    ProfilerScope( "FileDatabase::removeFilesFromDb vector" );

    const size_t pathsSize = paths.size();

    StringWr pathsListed = "( '";
    for( size_t i = 0; i < pathsSize - 1; ++i )
    {
        StringWr pathNormal = paths[i];

        auto pathSanitized = pathNormal;
        pathsListed += pathSanitized + "', '";
    }
    StringWr lastPath = paths[pathsSize - 1];
    pathsListed += lastPath + "')";

    StringWr sqlQuery = StringWr( "DELETE FROM FILES WHERE PATH IN " ) + pathsListed + ";";

    char* zErrMsg = nullptr;
    auto callback = []( void* thisPtrValue, int argc, char** argv, char** info )
    {
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.getUtfChar(), callback, nullptr, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        Assert::simple( false, "DB ERROR!" );
    }
}

FileDatabase::~FileDatabase()
{
    while( m_tasksCounter > 0 )
    {
        CUL::ITimer::sleepMiliSeconds( 4 );
    }

    m_update = false;
    m_cachedFileInserting.waitForCompletion();

    m_deleteRemnantsDone.get();
#if DO_NO_USE_SQLITE_MTX
    sqlite3_close( m_db );
#else   // DO_NO_USE_SQLITE_MTX
    sqlite3_close( m_db );
#endif  // DO_NO_USE_SQLITE_MTX
}

StringWr FileDatabase::sanitize( const StringWr& inString )
{
    StringWr normalized = inString;
    normalized.replace( "./", "" );
    normalized.replace( "'", "''" );
    normalized.removeAll( '\0' );
    return normalized;
}

StringWr FileDatabase::deSanitize( const StringWr& inString )
{
    StringWr normalized = inString;
    normalized.replace( "''", "'" );
    return normalized;
}

SortedStructuredListOfFiles::SortedStructuredListOfFiles()
{
}

SortedStructuredListOfFiles::SortedStructuredListOfFiles( const SortedStructuredListOfFiles& arg ): m_groupsBySize( arg.m_groupsBySize )
{
}

SortedStructuredListOfFiles::SortedStructuredListOfFiles( SortedStructuredListOfFiles&& arg ) noexcept
    : m_groupsBySize( std::move( arg.m_groupsBySize ) )
{
}

SortedStructuredListOfFiles& SortedStructuredListOfFiles::operator=( const SortedStructuredListOfFiles& arg )
{
    if( this != &arg )
    {
        m_groupsBySize = arg.m_groupsBySize;
    }
    return *this;
}

SortedStructuredListOfFiles& SortedStructuredListOfFiles::operator=( SortedStructuredListOfFiles&& arg ) noexcept
{
    if( this != &arg )
    {
        m_groupsBySize = std::move( arg.m_groupsBySize );
    }
    return *this;
}

void SortedStructuredListOfFiles::addFile( const FileInfo& arg )
{
    ProfilerScope( "SortedStructuredListOfFiles::addFile" );
    const std::uint64_t fileSize = arg.Size.toUint64();
    auto it = m_groupsBySize.find( fileSize );
    if( it == m_groupsBySize.end() )
    {
        MD5List list;
        list.Files[arg.MD5].insert( arg );
        m_groupsBySize[fileSize] = list;
    }
    else
    {
        MD5List& md5List = it->second;
        auto md5it = md5List.Files.find( arg.MD5 );
        if( md5it == md5List.Files.end() )
        {
            std::set<FileInfo> fileList;
            fileList.insert( arg );
            md5List.Files[arg.MD5] = fileList;
        }
        else
        {
            std::set<FileInfo>& fileSet = md5it->second;
            fileSet.insert( arg );
        }
    }
}

std::vector<std::int32_t> SortedStructuredListOfFiles::getPossibleSizes( EOrderType inOrderType ) const
{
    std::vector<std::int32_t> result;

    for( const auto& [size, _] : m_groupsBySize )
    {
        result.push_back( size );
    }

    if( inOrderType == EOrderType::Desc )
    {
        std::reverse( result.begin(), result.end() );
    }

    return result;
}

MD5List SortedStructuredListOfFiles::getMd5List( std::uint64_t inSize ) const
{
    MD5List result = m_groupsBySize[inSize];

    return result;
}

SortedStructuredListOfFiles::~SortedStructuredListOfFiles()
{
}

#if defined( DEBUG_THIS_FILE )
    #if defined( CUL_COMPILER_MSVC )
        #pragma optimize( "", on )
    #elif defined( CUL_COMPILER_CLANG )
        #pragma clang optimize on
    #elif defined( CUL_COMPILER_GCC )
        #pragma GCC pop_options
    #endif
#endif  // #if defined(DEBUG_THIS_FILE)

#ifdef _MSC_VER
    #pragma warning( pop )
#endif
