#include "CUL/Filesystem/FileDatabase.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/ITimer.hpp"
#include "Filesystem/FSUtils.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/Threading/MultiWorkerSystem.hpp"
#include "CUL/Threading/TaskCallback.hpp"
#include "CUL/Threading/ThreadUtil.hpp"

#include "IMPORT_sqlite3.hpp"
#include "CUL/IMPORT_tracy.hpp"
#include "CUL/STL_IMPORTS/STD_inttypes.hpp"

#ifdef _MSC_VER
    #pragma warning( push, 0 )
    #pragma warning( disable : 1404 )
#endif

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


#if defined( SQLITE_THREADSAFE ) && SQLITE_THREADSAFE == 0
    #pragma message("CUL SQLITE_THREADSAFE DISABLED.")
    #define DO_NO_USE_SQLITE_MTX 1
#else // defined( SQLITE_THREADSAFE ) && SQLITE_THREADSAFE == 0
    #pragma message( "CUL SQLITE_THREADSAFE ENABLED." )
    #define DO_NO_USE_SQLITE_MTX 0
#endif // defined( SQLITE_THREADSAFE ) && SQLITE_THREADSAFE == 0

#if DO_NO_USE_SQLITE_MTX
std::mutex g_sqliteMtx;
#else
#endif // DO_NO_USE_SQLITE_MTX

static FileDatabase* g_dbInstance = nullptr;

std::int32_t SQLiteQueryImpl( sqlite3* db, const char* query, int ( *callback )( void*, int, char**, char** ), void* firstArgument,
                          char** errmsg )
{
    ZoneScoped;
    std::int32_t rc = sqlite3_exec( db, query, callback, firstArgument, errmsg );
    return rc;
}

std::int32_t SQLiteQuery( sqlite3* db, const char* query, int ( *callback )( void*, int, char**, char** ), void* firstArgument, char** errmsg )
{
    ZoneScoped;
#if DO_NO_USE_SQLITE_MTX
    g_sqliteMtx.lock();
#endif // DO_NO_USE_SQLITE_MTX
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
    return ( Size == second.Size ) && ( MD5 == second.MD5 );
}

bool FileInfo::operator<( const FileInfo& second ) const
{
    return FilePath < second.FilePath;
}

FileDatabase::FileDatabase()
{
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
};

float FileDatabase::getPercentage() const
{
    return 100.f * m_current / ( 1.f * m_rowCount );
}

void FileDatabase::getListOfPossibleDuplicates( SortedStructuredListOfFiles& inOutPossibleDuplicates )
{
    ZoneScoped;

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
    ZoneScoped;
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
    ZoneScoped;
    std::vector<CUL::String> result;

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

    return result;
}

std::vector<CUL::String> FileDatabase::getListOfMd5( std::uint64_t inSize ) const
{
    ZoneScoped;
    std::vector<CUL::String> result;

    constexpr std::size_t bufferLength = 1024u;
    char buffer[bufferLength];
    snprintf( buffer, bufferLength, "SELECT DISTINCT MD5 FROM FILES WHERE SIZE=\"%I64u\";", inSize );

    auto callback = []( void* voidPtr, int, char** argv, char** )
    {
        CUL::String valueAsString = argv[0];
        std::vector<CUL::String>* resulPtr = reinterpret_cast<std::vector<CUL::String>*>( voidPtr );
        resulPtr->push_back( valueAsString );

        return 0;
    };

    char* zErrMsg = nullptr;
    std::int32_t rc = SQLiteQuery( m_db, buffer, callback, &result, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        Assert::check( false, "DB ERROR: %s", zErrMsg );
    }

    return result;
}

void FileDatabase::getFiles( uint64_t size, const CUL::String& md5, std::vector<FileInfo>& out ) const
{
    ZoneScoped;
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

void FileDatabase::getFiles( uint64_t size, std::vector<FileInfo>& out ) const
{
    ZoneScoped;
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
    ZoneScoped;
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
    ZoneScoped;
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

int64_t FileDatabase::getFileCount() const
{
    ZoneScoped;
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

void FileDatabase::initDb()
{
    constexpr std::size_t sizeOfWchar = sizeof( wchar_t );

    ZoneScoped;
    ThreadUtil::getInstance().setThreadStatus( "Initi db..." );
    int rc = sqlite3_open( m_databasePath.getPath().cStr(), &m_db );

    constexpr std::size_t bufferLength = 1024u;
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
        const std::int32_t writeSize = snprintf( sqlQueryBuffor, bufferLength, "CREATE TABLE FILES (\
        PATH BINARY(2048),\
        SIZE BIGINT(255),\
        MD5 varchar(1024),\
        LAST_MODIFICATION varchar(1024),\
        CONSTRAINT PATH PRIMARY KEY (PATH) \
        );" );
        Assert::simple( writeSize < 1, "Query input wrong! Command is too long!" );

        std::string errorResult( zErrMsg );
        rc = sqlite3_exec( m_db, sqlQueryBuffor, callback, 0, &zErrMsg );
        if(rc != SQLITE_OK)
        {
            Assert::simple( false, "DB ERROR!" );
        }
    }

    ThreadUtil::getInstance().setThreadStatus( "Initi db... done." );
    m_initialized = true;
}

void FileDatabase::addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime )
{
    ZoneScoped;

    String filePathNormalized = filePath;
    filePathNormalized.sanitize();
    auto foundFile = getFileInfo( filePath );
    char* zErrMsg = nullptr;
    auto callback = []( void*, int, char**, char** )
    {
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    String sqlQuery = "";
    if( foundFile.Found )
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

    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.cStr(), callback, nullptr, &zErrMsg );
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

FileInfo FileDatabase::getFileInfo( const String& path ) const
{
    ZoneScoped;

    ThreadString info = "FileDatabase::getFileInfo: " + path.string();
    ThreadUtil::getInstance().setThreadStatus( info );
    waitForInit();
    FileInfo result;
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
        ZoneScoped;
        String path( argv[0] );
        auto fileInfoFromPtr = reinterpret_cast<FileInfo*>( fileInfoPtr );
        fileInfoFromPtr->Found = true;
        fileInfoFromPtr->MD5 = argv[2];
        fileInfoFromPtr->Size = argv[1];
        fileInfoFromPtr->ModTime.fromString( argv[3] );

        return 0;
    };
    char* zErrMsg = nullptr;

    std::int32_t rc = SQLiteQuery( m_db, sqlQuery.cStr(), callback, &result, &zErrMsg );
    result.FilePath = pathInBinary;

    constexpr bool PrintInfo = false;
    if( PrintInfo && !result.Found )
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
    ZoneScoped;
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
    ZoneScoped;
    ThreadString info = "FileDatabase::removeFileFromDB: " + pathRaw.string();
    ThreadUtil::getInstance().setThreadStatus( info );

    constexpr std::size_t bufferSize{512};
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

    if(rc != SQLITE_OK)
    {
        Assert::simple( false, "DB ERROR!" );
    }
}


void FileDatabase::removeFilesFromDb( const std::vector<CUL::String>& paths )
{
    ZoneScoped;
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

SortedStructuredListOfFiles::SortedStructuredListOfFiles( const SortedStructuredListOfFiles& arg ) : m_groupsBySize( arg.m_groupsBySize )
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
