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

void EscapeCharacters( String& inOutString )
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
    std::vector<String> FilesList{};
    std::deque<String> RemoveList{};
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

        CUL::String filePath( argv[0] );
        const CUL::String size = argv[1];
        const CUL::String md5 = argv[2];
        const CUL::String lastMod = argv[3];
        FileInfo fi;
        fi.FilePath = filePath;
        CUL::String pathCopy = fi.FilePath.getPath();
        if( pathCopy.empty() == false )
        {
            pathCopy.singleQuoteRestore();
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
        for( const FileInfo& fi : m_cachedFiles )
        {
            sizes.insert( fi.Size.toUint64() );
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
        String valueAsString = argv[0];
        std::vector<uint64_t>* resulPtr = reinterpret_cast<std::vector<uint64_t>*>( voidPtr );
        resulPtr->push_back( valueAsString.toUint64() );

        return 0;
    };

    char* zErrMsg = nullptr;
    const std::int32_t rc = SQLiteQuery( m_db, sqlQuery.c_str(), callback, &out, &zErrMsg );

    if( ( rc != SQLITE_OK ) && ( rc != SQLITE_MISUSE ) )
    {
        if( String::cmp( zErrMsg, "no such table" ) != 0 )  // new database.
        {
            Assert::check( false, "DB ERROR: %s", zErrMsg );
        }
    }
}

std::vector<CUL::String> FileDatabase::getListOfMd5() const
{
    ProfilerScope( "FileDatabase::getListOfMd5 void" );
    std::vector<CUL::String> result;
#if USE_CACHE
    std::set<CUL::String> md5s;
    {
        std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
        for( const FileInfo& fi : m_cachedFiles )
        {
            md5s.insert( fi.MD5 );
        }
    }
    {
        for( const CUL::String& md5 : md5s )
        {
            result.push_back( md5 );
        }
    }

#else   // #if USE_CACHE
    const std::string sqlQuery = std::string( "SELECT DISTINCT MD5 FROM FILES ORDER BY SIZE;" );
    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        CUL::String valueAsString = argv[0];
        std::vector<CUL::String>* resulPtr = reinterpret_cast<std::vector<CUL::String>*>( voidPtr );
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

std::vector<CUL::String> FileDatabase::getListOfMd5( std::uint64_t inSize ) const
{
    ProfilerScope( "FileDatabase::getListOfMd5 inSize" );
    std::vector<CUL::String> result;
#if USE_CACHE
    std::set<CUL::String> md5s;
    {
        std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
        for( const FileInfo& fi : m_cachedFiles )
        {
            if( fi.Size.toUint64() == inSize )
            {
                md5s.insert( fi.MD5 );
            }
        }
    }
    {
        for( const CUL::String& md5 : md5s )
        {
            result.push_back( md5 );
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

void FileDatabase::getFiles( uint64_t inSize, const CUL::String& md5, std::vector<FileInfo>& out ) const
{
#if USE_CACHE
    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
    for( const FileInfo& fi : m_cachedFiles )
    {
        if( ( fi.Size.toUint64() == inSize ) && ( fi.MD5 == md5 ) )
        {
            out.push_back( fi );
        }
    }
#else
    getFilesFromDB( size, md5, out );
#endif
}

void FileDatabase::getFilesFromDB( uint64_t size, const CUL::String& md5, std::vector<FileInfo>& out ) const
{
    ProfilerScope( "FileDatabase::getFiles" );
    const CUL::String sqlQuery = CUL::String( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES WHERE SIZE=\"" ) + CUL::String( size ) +
                                 "\" AND MD5=\"" + md5 + "\";";
    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        CUL::String filePath( argv[0] );
        const CUL::String size = argv[1];
        const CUL::String md5 = argv[2];
        const CUL::String lastMod = argv[3];
        auto resulPtr = reinterpret_cast<std::vector<FileInfo>*>( voidPtr );
        FileInfo fi;
        fi.FilePath = filePath;
        CUL::String pathCopy = fi.FilePath.getPath();
        if( pathCopy.empty() == false )
        {
            pathCopy.singleQuoteRestore();
            fi.FilePath = pathCopy;
        }

        fi.MD5 = md5;
        fi.ModTime.fromString( lastMod );
        fi.Size = size;
        resulPtr->push_back( fi );

        return 0;
    };

    char* zErrMsg = nullptr;
    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.cStr(), callback, &out, &zErrMsg );

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

    for( const FileInfo& fi : m_cachedFiles )
    {
        if( fi.Size.toUint64() == inSize )
        {
            out.push_back( fi );
        }
    }
#else
    getFilesFromDb( size, out );
#endif
}

void FileDatabase::getFilesFromDB( uint64_t size, std::vector<FileInfo>& out ) const
{
    ProfilerScope( "FileDatabase::getFiles" );

    const CUL::String sqlQuery =
        CUL::String( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES WHERE SIZE=\"" ) + CUL::String( size ) + "\";";
    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        CUL::String filePath( argv[0] );
        const CUL::String size = argv[1];
        const CUL::String md5 = argv[2];
        const CUL::String lastMod = argv[3];
        auto resulPtr = reinterpret_cast<std::vector<FileInfo>*>( voidPtr );
        FileInfo fi;
        filePath.singleQuoteRestore();
        fi.FilePath = filePath;
        fi.MD5 = md5;
        fi.ModTime.fromString( lastMod );
        fi.Size = size;
        resulPtr->push_back( fi );

        return 0;
    };

    char* zErrMsg = nullptr;
    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.cStr(), callback, &out, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        Assert::check( false, "DB ERROR: %s", zErrMsg );
    }
}

void FileDatabase::loadFilesFromDatabase()
{
    ProfilerScope( "FileDatabase::loadFilesFromDatabase" );
    ;
    ThreadUtil::getInstance().setThreadStatus( "FileDatabase::loadFilesFromDatabase::initDb();" );
    initDb();

    std::lock_guard<std::mutex> locker( m_fetchListMtx );
    m_fetchList = new ListAndApi();

    m_fetchList->thisPtr = this;
    m_fetchList->FS_API = CUL::CULInterface::getInstance()->getFS();
    m_fetchList->m_currentFileIndex = &m_current;
}

void FileDatabase::getFilesMatching( const CUL::String& fileSize, const CUL::String& md5, std::list<CUL::String>& out ) const
{
    ProfilerScope( "FileDatabase::getFilesMatching" );
    ;
    String sqlQuery = String( "SELECT PATH FROM FILES WHERE ( SIZE='" ) + fileSize + "' AND MD5='" + md5 + "');";

    char* zErrMsg = nullptr;
    auto callback = []( void* voidValue, int argc, char** argv, char** info )
    {
        std::list<CUL::String>* resultPtr = reinterpret_cast<std::list<CUL::String>*>( voidValue );
        CUL::String foundPath( argv[0] );
        resultPtr->push_back( foundPath );
        return 0;
    };

    std::string sqlQuerySTR = sqlQuery.string();
    std::int32_t rc = SQLiteQuery( m_db, sqlQuerySTR.c_str(), callback, &out, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::simple( false, "DB ERROR!" );
    }
}

CacheUsage FileDatabase::getCacheUsage() const
{
    CacheUsage result;
    {
        std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
        result.Curr = static_cast<decltype( result.Curr )>( m_cachedFiles.size() );
        result.Max = static_cast<decltype( result.Max )>( m_cachedFilesMax );
    }

    constexpr static std::size_t sizeOfOne = sizeof( CacheUsage );
    result.MBUsed = result.Curr * sizeOfOne;  // How many Bytes.
    result.MBUsed /= 1024.f;                  // How many KiloBytes.
    result.MBUsed /= 1024.f;                  // How many MegaBytes.

    result.Percentage = static_cast<float>( result.Curr ) / static_cast<float>( result.Max );
    return result;
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
        String valueAsString = argv[0];
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

std::optional<FileInfo> FileDatabase::getFromCache( const String& inFilePath ) const
{
    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );

    const auto it = std::find_if( m_cachedFiles.begin(), m_cachedFiles.end(),
                                  [&inFilePath]( const FileInfo& curr )
                                  {
                                      return curr.FilePath.getPath() == inFilePath;
                                  } );

    if( it != m_cachedFiles.end() )
    {
        return *it;
    }

    return {};
}

bool FileDatabase::removeFromCache( const String& inFilePath )
{
    std::lock_guard<std::mutex> locker( m_cachedFilesMtx );
    const std::list<FileInfo>::iterator it = std::find_if( m_cachedFiles.begin(), m_cachedFiles.end(),
                                                           [&inFilePath]( const FileInfo& curr )
                                                           {
                                                               return curr.FilePath.getPath() == inFilePath;
                                                           } );

    if( it != m_cachedFiles.end() )
    {
        m_cachedFiles.erase( it );
        return true;
    }
    return false;
}

void FileDatabase::addToCache( const FileInfo& inFile )
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

    for( const FileInfo& fi : m_cachedFiles )
    {
        if( fi == inFile )
        {
            return;
        }
    }

    m_cachedFiles.push_back( inFile );
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
    int rc = sqlite3_open( m_databasePath.getPath().cStr(), &m_db );

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
    std::int64_t md5It = 0;
    std::int64_t maxMd5s = 4;
    std::vector<CUL::FS::FileInfo> sameSizeFiles;
    for( std::int64_t i = listOfSizesSize - 1; i >= 0; --i )
    {
        ProfilerScope( "FileDatabase::updateCache it 1" );
        const auto size = listOfSizes[i];
        getFilesFromDB( size, sameSizeFiles );
        for( const CUL::FS::FileInfo& fi : sameSizeFiles )
        {
            ProfilerScope( "FileDatabase::updateCache it 2" );
            addToCache( fi );
        }
        sameSizeFiles.clear();
    }
}

void FileDatabase::addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime )
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

void FileDatabase::addFileImpl( ELockType inLockType, MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize,
                                const CUL::String& modTime )
{
    ProfilerScope( "FileDatabase::addFile" );

    String filePathNormalized = filePath;
    filePathNormalized.sanitize();
    std::optional<FileInfo> foundFile = getFileInfo_Impl( inLockType, filePath );
    char* zErrMsg = nullptr;
    auto callback = []( void*, int, char**, char** )
    {
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    String sqlQuery = "";
    if( foundFile )
    {
        const std::string binaryForm = filePathNormalized.cStr();
        sqlQuery = "UPDATE FILES SET SIZE='" + fileSize + "', MD5='" + md5 + "', LAST_MODIFICATION='" + modTime + "' WHERE PATH='" +
                   binaryForm + "'";

        // CUL::LOG::ILogger::getInstance()->log( "Found updated file: " + filePath );
        // CUL::LOG::ILogger::getInstance()->log( "New/Old diff: ");

        // CUL::LOG::ILogger::getInstance()->log( "[OLD] MD5: " + foundFile.MD5 );
        // CUL::LOG::ILogger::getInstance()->log( "[NEW] MD5: " + md5 );

        // CUL::LOG::ILogger::getInstance()->log( "[OLD] SIZE: " + foundFile.Size );
        // CUL::LOG::ILogger::getInstance()->log( "[NEW] SIZE: " + fileSize );

        // CUL::LOG::ILogger::getInstance()->log( "[OLD] modTime: " + foundFile.ModTime );
        // CUL::LOG::ILogger::getInstance()->log( "[NEW] modTime: " + modTime );
    }
    else
    {
        const std::string binaryValue = filePathNormalized.cStr();

        constexpr std::size_t bufferLength = 1024u;
        char buffer[bufferLength];
        snprintf( buffer, bufferLength, "INSERT INTO FILES (PATH, SIZE, MD5, LAST_MODIFICATION ) VALUES ( '%s', '%s', '%s', '%s' );",
                  binaryValue.c_str(), fileSize.cStr(), md5.cStr(), modTime.cStr() );
        sqlQuery = buffer;
    }

    std::int32_t rc{ 0 };

    if( inLockType == ELockType::Locked )
    {
        rc = SQLiteQuery( m_db, sqlQuery.cStr(), callback, nullptr, &zErrMsg );
    }
    else
    {
        rc = SQLiteQueryImpl( m_db, sqlQuery.cStr(), callback, nullptr, &zErrMsg );
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

std::optional<FileInfo> FileDatabase::getFileInfo( const String& path ) const
{
    ProfilerScope( "FileDatabase::getFileInfo" );
    std::optional<FileInfo> fromCache = getFromCache( path );
    if( fromCache )
    {
        return fromCache.value();
    }

    return getFileInfo_Impl( ELockType::Locked, path );
}

std::optional<FileInfo> FileDatabase::getFileInfo_Impl( ELockType inLockType, const String& path ) const
{
    ProfilerScope( "FileDatabase::getFileInfo" );
    std::optional<FileInfo> result;

    waitForInit();
    String pathInBinary = path;
    pathInBinary.sanitize();
    const std::string binaryForm = pathInBinary.cStr();
    String sqlQuery =
        "SELECT * \
FROM FILES \
WHERE PATH='" +
        binaryForm + "';";
    pathInBinary.singleQuoteRestore();

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
        rc = SQLiteQuery( m_db, sqlQuery.cStr(), callback, &result, &zErrMsg );
    }
    else
    {
        rc = SQLiteQueryImpl( m_db, sqlQuery.cStr(), callback, &result, &zErrMsg );
    }

    if( result )
    {
        result->FilePath = pathInBinary;
    }

    constexpr bool PrintInfo = false;
    if( PrintInfo && !result )
    {
        LOG::ILogger::getInstance().log( "[FileDatabase::getFileInfo] Could not find: " + path );
        LOG::ILogger::getInstance().log( "[FileDatabase::getFileInfo] Used SQL command: " + sqlQuery );
    }

    if( rc != SQLITE_OK )
    {
        Assert::check( false, "DB ERROR: %s", zErrMsg );
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

void FileDatabase::removeFileFromDB( const CUL::String& pathRaw )
{
    ProfilerScope( "FileDatabase::removeFileFromDB" );
    removeFromCache( pathRaw );
    removeFileFromDB_Impl( pathRaw );
}

void FileDatabase::removeFileFromDB_Impl( const CUL::String& pathRaw )
{
    ProfilerScope( "FileDatabase::removeFileFromDB" );

    ThreadString info = "FileDatabase::removeFileFromDB: " + pathRaw.string();
    ThreadUtil::getInstance().setThreadStatus( info );

    constexpr std::size_t bufferSize{ 512 };
    static char buffer[bufferSize];
    snprintf( buffer, bufferSize, "FileDatabase::removeFileFromDB pathRaw: %s", pathRaw.cStr() );
    ThreadUtil::getInstance().setThreadStatus( buffer );
    String path = pathRaw;
    path.sanitize();

    const std::string binaryForm = path.cStr();
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

void FileDatabase::removeFilesFromDb( const std::vector<CUL::String>& paths )
{
    ProfilerScope( "FileDatabase::removeFilesFromDb vector" );

    const size_t pathsSize = paths.size();

    String pathsListed = "( '";
    for( size_t i = 0; i < pathsSize - 1; ++i )
    {
        String pathNormal = paths[i];

        auto pathSanitized = pathNormal;
        pathsListed += pathSanitized + "', '";
    }
    String lastPath = paths[pathsSize - 1];
    pathsListed += lastPath + "')";

    String sqlQuery = String( "DELETE FROM FILES WHERE PATH IN " ) + pathsListed + ";";

    char* zErrMsg = nullptr;
    auto callback = []( void* thisPtrValue, int argc, char** argv, char** info )
    {
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.cStr(), callback, nullptr, &zErrMsg );

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

String FileDatabase::sanitize( const String& inString )
{
    CUL::String normalized = inString;
    normalized.replace( "./", "" );
    normalized.replace( "'", "''" );
    normalized.removeAll( '\0' );
    return normalized;
}

String FileDatabase::deSanitize( const String& inString )
{
    String normalized = inString;
    normalized.replace( "''", "'" );
    return normalized;
}

SortedStructuredListOfFiles::SortedStructuredListOfFiles()
{
}

SortedStructuredListOfFiles::SortedStructuredListOfFiles( const SortedStructuredListOfFiles& arg ): m_groupsBySize( arg.m_groupsBySize )
{
}

SortedStructuredListOfFiles::SortedStructuredListOfFiles( SortedStructuredListOfFiles&& arg )
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

SortedStructuredListOfFiles& SortedStructuredListOfFiles::operator=( SortedStructuredListOfFiles&& arg )
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
