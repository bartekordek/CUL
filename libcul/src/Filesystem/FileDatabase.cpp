#include "CUL/Filesystem/FileDatabase.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/ITimer.hpp"
#include "Filesystem/FSUtils.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/Threading/MultiWorkerSystem.hpp"
#include "CUL/Threading/TaskCallback.hpp"
#include "CUL/Threading/ThreadUtil.hpp"

#include "CUL/IMPORT_sqlite3.hpp"
#include "CUL/IMPORT_tracy.hpp"

#ifdef _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 1404 )
#endif

using namespace CUL;
using namespace FS;

#if 0 // DEBUG_THIS_FILE
    #define DEBUG_THIS_FILE 1

    #if defined(CUL_COMPILER_MSVC)
        #pragma optimize( "", off )
    #elif defined(CUL_COMPILER_CLANG)
        #pragma clang optimize off
    #elif defined(CUL_COMPILER_GCC)
        #pragma GCC push_options
        #pragma GCC optimize( "O0" )
    #endif
#endif

static FileDatabase* g_dbInstance = nullptr;

void EscapeCharacters(String& inOutString)
{
    inOutString.replace( "\\", "\\\\" );
}

bool FileDatabase::FileInfo::operator==( const FileInfo& second ) const
{
    return ( Size == second.Size ) && ( MD5 == second.MD5 );
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
    CUL::FS::FSApi* FS_API = nullptr;
    std::atomic<int64_t>* m_currentFileIndex = nullptr;
};

float FileDatabase::getPercentage() const
{
    return 100.f * m_current / ( 1.f * m_rowCount );
}

void FileDatabase::getListOfSizes( std::vector<uint64_t>& out ) const
{
    ZoneScoped;
    const std::string sqlQuery = std::string( "SELECT DISTINCT SIZE FROM FILES ORDER BY SIZE;" );
    auto callback = []( void* voidPtr, int, char** argv, char** ) {
        CUL::String valueAsString = argv[0];
        std::vector<uint64_t>* resulPtr = reinterpret_cast<std::vector<uint64_t>*>( voidPtr );
        resulPtr->push_back( valueAsString.toUint64() );

        return 0;
    };

    char* zErrMsg = nullptr;
    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, &out, &zErrMsg );

    if( ( rc != SQLITE_OK ) && ( rc != SQLITE_MISUSE ) )
    {
        if(String::cmp(zErrMsg, "no such table") != 0) // new database.
        {
            CUL::Assert::check(false, "DB ERROR: %s", zErrMsg);
        }
    }
}

std::vector<CUL::String> FileDatabase::getListOfMd5() const
{
    ZoneScoped;
    std::vector<CUL::String> result;

    const std::string sqlQuery = std::string( "SELECT DISTINCT MD5 FROM FILES ORDER BY SIZE;" );
    auto callback = []( void* voidPtr, int, char** argv, char** ) {
        CUL::String valueAsString = argv[0];
        std::vector<CUL::String>* resulPtr = reinterpret_cast<std::vector<CUL::String>*>( voidPtr );
        resulPtr->push_back( valueAsString );

        return 0;
    };

    char* zErrMsg = nullptr;
    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, &result, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::check(false, "DB ERROR: %s", zErrMsg);
    }

    return result;
}

void FileDatabase::getFiles( uint64_t size, const CUL::String& md5, std::vector<FileInfo>& out ) const
{
    ZoneScoped;
    const CUL::String sqlQuery = CUL::String( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES WHERE SIZE=\"" ) + CUL::String( size ) + "\" AND MD5=\"" + md5 + "\";";
    auto callback = []( void* voidPtr, int, char** argv, char** ) {
        CUL::String filePath( argv[0] );
        const CUL::String size = argv[1];
        const CUL::String md5 = argv[2];
        const CUL::String lastMod = argv[3];
        auto resulPtr = reinterpret_cast<std::vector<FileDatabase::FileInfo>*>( voidPtr );
        FileInfo fi;
        fi.FilePath = filePath;
        CUL::String pathCopy = fi.FilePath.getPath();
        if( pathCopy.empty() == false )
        {
            pathCopy.singleQuoteRestore();
            fi.FilePath = pathCopy;
        }

        fi.MD5 = md5;
        fi.ModTime = lastMod;
        fi.Size = size;
        resulPtr->push_back( fi );

        return 0;
    };

    char* zErrMsg = nullptr;
    int rc = sqlite3_exec( m_db, sqlQuery.cStr(), callback, &out, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::check(false, "DB ERROR: %s", zErrMsg);
    }
}

void FileDatabase::getFiles( uint64_t size, std::vector<FileInfo>& out ) const
{
    ZoneScoped;
    const CUL::String sqlQuery = CUL::String( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES WHERE SIZE=\"" ) + CUL::String( size ) + "\";";
    auto callback = []( void* voidPtr, int, char** argv, char** ) {
        CUL::String filePath( argv[0] );
        const CUL::String size = argv[1];
        const CUL::String md5 = argv[2];
        const CUL::String lastMod = argv[3];
        auto resulPtr = reinterpret_cast<std::vector<FileDatabase::FileInfo>*>( voidPtr );
        FileInfo fi;
        filePath.singleQuoteRestore();
        fi.FilePath = filePath;
        fi.MD5 = md5;
        fi.ModTime = lastMod;
        fi.Size = size;
        resulPtr->push_back( fi );

        return 0;
    };

    char* zErrMsg = nullptr;
    int rc = sqlite3_exec( m_db, sqlQuery.cStr(), callback, &out, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::check( false, "DB ERROR: %s", zErrMsg);
    }
}

void FileDatabase::loadFilesFromDatabase()
{
    ZoneScoped;
    CUL::ThreadUtil::getInstance().setThreadStatus( "FileDatabase::loadFilesFromDatabase::initDb();" );
    initDb();

    std::lock_guard<std::mutex> locker( m_fetchListMtx );
    m_fetchList = new ListAndApi();

    m_fetchList->thisPtr = this;
    m_fetchList->FS_API = CUL::CULInterface::getInstance()->getFS();
    m_fetchList->m_currentFileIndex = &m_current;

    CUL::FS::FSApi* fsApi = CUL::CULInterface::getInstance()->getFS();

    std::string sqlQuery = std::string( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES" );
    auto callback = []( void* thisPtrValue, int, char** argv, char** )
    {
        ZoneScoped;
        ListAndApi* rd = reinterpret_cast<ListAndApi*>( thisPtrValue );
        String file( argv[0] );
        file.singleQuoteRestore();

        if( file.find( L"descriptorsets_vk.cpp" ) != -1 )
        {
            auto x = 0;
            String filex( argv[0] );
        }

        rd->FilesList.push_back( file );
        ++*rd->m_currentFileIndex;

        return 0;
    };

    CUL::ThreadUtil::getInstance().setThreadStatus( "FileDatabase::loadFilesFromDatabase::getFileCount();" );
    m_rowCount = getFileCount();

    char* zErrMsg = nullptr;
    CUL::ThreadUtil::getInstance().setThreadStatus( "FileDatabase::loadFilesFromDatabase::fetch();" );
    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, m_fetchList, &zErrMsg );

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
            CUL::Assert::simple( false, "DB ERROR!" );
        }
    }
    else
    {
        constexpr bool mt = true;
        if( mt )
        {
            CUL::TaskCallback* taskCbck = new CUL::TaskCallback();
            taskCbck->Type = ITask::EType::DeleteAfterExecute;
            taskCbck->Callback = [this]( int8_t /*workerId*/ ) {
                CUL::ThreadUtil::getInstance().setThreadStatus( "FileDatabase::loadFilesFromDatabase::deleteRemnants();" );
                deleteRemnants();
            };

            CUL::MultiWorkerSystem::getInstance().registerTask( taskCbck );
        }
        else
        {
            deleteRemnants();
        }
    }
}

bool FileDatabase::deleteRemnants()
{
    ZoneScoped;
    std::string status = "loadFilesFromDatabase -> deleting remnants...";
    ThreadUtil::getInstance().setThreadStatus( status );

    if( m_fetchList == nullptr )
    {
        return false;
    }

    size_t filesCount = m_fetchList->FilesList.size();

    status = "loadFilesFromDatabase -> deleting remnants... collecting not existing files...";
    CUL::ThreadUtil::getInstance().setThreadStatus( status );

    for( size_t i = 0; i < filesCount; ++i )
    {
        const float perc = 100.f * ( i + 1 ) / ( 1.f * filesCount );

        if( !m_fetchList->FS_API->fileExist( m_fetchList->FilesList[i] ) )
        {
            CUL::TaskCallback* removetask = new CUL::TaskCallback();
            removetask->Type = ITask::EType::DeleteAfterExecute;
            const String filePath = m_fetchList->FilesList[i];
            removetask->Callback = [this, filePath]( int8_t ) {
                removeFileFromDB( filePath );
            };
            CUL::MultiWorkerSystem::getInstance().registerTask( removetask );
        }

        const String status = "loadFilesFromDatabase -> deleting remnants... collecting not existing files..." + CUL::String( perc );
        CUL::ThreadUtil::getInstance().setThreadStatus( status.cStr() );
    }

    CUL::ThreadUtil::getInstance().setThreadStatus( "loadFilesFromDatabase -> deleting remnants... collecting not existing files... done." );

    filesCount = m_fetchList->RemoveList.size();

    m_fetchList->RemoveList.clear();

    return true;
}

void FileDatabase::getFilesMatching( const CUL::String& fileSize, const CUL::String& md5, std::list<CUL::String>& out ) const
{
    ZoneScoped;
    CUL::String sqlQuery = CUL::String( "SELECT PATH FROM FILES WHERE ( SIZE='" ) + fileSize + "' AND MD5='" + md5 + "');";

    char* zErrMsg = nullptr;
    auto callback = [] ( void* voidValue, int argc, char** argv, char** info ){
        std::list<CUL::String>* resultPtr = reinterpret_cast<std::list<CUL::String>*>( voidValue );
        CUL::String foundPath( argv[0] );
        resultPtr->push_back( foundPath );
        return 0;
    };

    std::string sqlQuerySTR = sqlQuery.string();
    int rc = sqlite3_exec( m_db, sqlQuerySTR.c_str(), callback, &out, &zErrMsg );

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
    //std::string sqlQuery = std::string( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES" );
    std::string sqlQuery = std::string( "SELECT COUNT(PATH) as something from FILES" );
    auto callback = [] ( void* voidPtr, int, char** argv, char** ){

        CUL::String valueAsString = argv[0];
        auto resulPtr = reinterpret_cast<int64_t*>( voidPtr );
        *resulPtr = valueAsString.toInt64();

        return 0;
    };

    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, &result, &zErrMsg );


    if( rc != SQLITE_OK )
    {
        CUL::Assert::check( false, "DB ERROR: %s", zErrMsg);
    }

    return result;
}

void FileDatabase::initDb()
{
    constexpr std::size_t sizeOfWchar = sizeof( wchar_t );

    ZoneScoped;
    CUL::ThreadUtil::getInstance().setThreadStatus( "Initi db..." );
    int rc = sqlite3_open( m_databasePath.getPath().cStr(), &m_db );

    std::string sqlQuery =
        "SELECT * \
    FROM FILES";
    auto callback = [] ( void*, int, char**, char** )    {
        // DuplicateFinder::s_instance->callback(NotUsed, argc, argv, azColName);
        return 0;
    };

    char* zErrMsg = nullptr;
    rc = sqlite3_exec( m_db, sqlQuery.c_str(), nullptr, 0, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        sqlQuery =
            "CREATE TABLE FILES (\
        PATH BINARY(2048),\
        SIZE BIGINT(255),\
        MD5 varchar(1024),\
        LAST_MODIFICATION varchar(1024),\
        CONSTRAINT PATH PRIMARY KEY (PATH) \
        );";
        std::string errorResult( zErrMsg );
        rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, 0, &zErrMsg );
        if( rc != SQLITE_OK )
        {
            CUL::Assert::simple( false, "DB ERROR!" );
        }
    }
    CUL::ThreadUtil::getInstance().setThreadStatus( "Initi db... done." );
    m_initialized = true;
}

void FileDatabase::addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime )
{
    ZoneScoped;
    CUL::String filePathNormalized = filePath;
    filePathNormalized.singleQuoteEscape();
    auto foundFile = getFileInfo( filePath );
    char* zErrMsg = nullptr;
    auto callback = [] ( void*, int, char**, char** ){
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    CUL::String sqlQuery = "";
    if( foundFile.Found )
    {
        const std::string binaryForm = filePathNormalized.cStr();
        sqlQuery = "UPDATE FILES SET SIZE='" + fileSize + "', MD5='" + md5 + "', LAST_MODIFICATION='" + modTime + "' WHERE PATH='" +
                   binaryForm + "'";

        //CUL::LOG::ILogger::getInstance()->log( "Found updated file: " + filePath );
        //CUL::LOG::ILogger::getInstance()->log( "New/Old diff: ");

        //CUL::LOG::ILogger::getInstance()->log( "[OLD] MD5: " + foundFile.MD5 );
        //CUL::LOG::ILogger::getInstance()->log( "[NEW] MD5: " + md5 );

        //CUL::LOG::ILogger::getInstance()->log( "[OLD] SIZE: " + foundFile.Size );
        //CUL::LOG::ILogger::getInstance()->log( "[NEW] SIZE: " + fileSize );

        //CUL::LOG::ILogger::getInstance()->log( "[OLD] modTime: " + foundFile.ModTime );
        //CUL::LOG::ILogger::getInstance()->log( "[NEW] modTime: " + modTime );
    }
    else
    {
        const std::string binaryValue = filePathNormalized.cStr();
        sqlQuery = "INSERT INTO FILES (PATH, SIZE, MD5, LAST_MODIFICATION ) VALUES ('" + binaryValue + "', '" + fileSize +
            "', '" + md5 + "', '" + modTime + "');";
    }

    const char* queryAsCharPtr = sqlQuery.cStr();
    int rc = sqlite3_exec( m_db, sqlQuery.cStr(), callback, 0, &zErrMsg );
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
            CUL::Assert::simple( false, "DB ERROR!" );
        }
    }
}

FileDatabase::FileInfo FileDatabase::getFileInfo( const String& path ) const
{
    ZoneScoped;
    waitForInit();
    FileDatabase::FileInfo result;
    String pathInBinary = path;
    pathInBinary.singleQuoteEscape();
    const std::string binaryForm = pathInBinary.cStr();
    String sqlQuery =
        "SELECT * \
FROM FILES \
WHERE PATH='" +
        binaryForm + "';";
    pathInBinary.singleQuoteRestore();

    const char* queryAsCharPtr = sqlQuery.cStr();
    auto callback = [] ( void* fileInfoPtr, int argc, char** argv, char** info ){
        CUL::String path( argv[0] );
        auto fileInfoFromPtr = reinterpret_cast<FileDatabase::FileInfo*>( fileInfoPtr );
        fileInfoFromPtr->Found = true;
        fileInfoFromPtr->MD5 = argv[2];
        fileInfoFromPtr->Size = argv[1];
        fileInfoFromPtr->ModTime = argv[3];

        return 0;
    };
    char* zErrMsg = nullptr;

    int rc = sqlite3_exec( m_db, sqlQuery.cStr(), callback, &result, &zErrMsg );
    result.FilePath = pathInBinary;

    constexpr bool PrintInfo = false;
    if( PrintInfo  && !result.Found )
    {
        LOG::ILogger::getInstance().log( "[FileDatabase::getFileInfo] Could not find: " + path );
        LOG::ILogger::getInstance().log( "[FileDatabase::getFileInfo] Used SQL command: " + sqlQuery );
    }

    if( rc != SQLITE_OK )
    {
        CUL::Assert::check( false, "DB ERROR: %s", zErrMsg );
    }

    return result;
}

void FileDatabase::waitForInit() const
{
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
    constexpr std::size_t bufferSize{ 512 };
    static char buffer[bufferSize];
    snprintf( buffer, bufferSize, "FileDatabase::removeFileFromDB pathRaw: %s", pathRaw.cStr() );
    CUL::ThreadUtil::getInstance().setThreadStatus( buffer );
    CUL::String path = pathRaw;
    path.singleQuoteEscape();

    const std::string binaryForm = path.cStr();
    std::string sqlQuery = std::string( "DELETE FROM FILES WHERE PATH='" ) + binaryForm + "';";

    char* zErrMsg = nullptr;
    auto callback = []( void* thisPtrValue, int argc, char** argv, char** info )
    {
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, this, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::simple( false, "DB ERROR!" );
    }
}

void FileDatabase::removeFilesFromDb( const std::vector<CUL::String>& paths )
{
    ZoneScoped;
    const size_t pathsSize = paths.size();

    CUL::String pathsListed = "( '";
    for( size_t i = 0; i < pathsSize - 1; ++i )
    {
        CUL::String pathNormal = paths[i];

        auto pathSanitized = pathNormal;
        pathsListed += pathSanitized + "', '";
    }
    CUL::String lastPath = paths[pathsSize - 1];
    pathsListed += lastPath + "')";

    CUL::String sqlQuery = CUL::String( "DELETE FROM FILES WHERE PATH IN " ) + pathsListed + ";";

    char* zErrMsg = nullptr;
    auto callback = [] ( void* thisPtrValue, int argc, char** argv, char** info )    {
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    std::string sqlQuerySTR = sqlQuery.string();
    int rc = sqlite3_exec( m_db, sqlQuerySTR.c_str(), callback, this, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::simple( false, "DB ERROR!" );
    }
}

FileDatabase::~FileDatabase()
{
    m_deleteRemnantsDone.get();
    sqlite3_close( m_db );
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
    CUL::String normalized = inString;
    normalized.replace( "''", "'" );
    return normalized;
}


#if defined( DEBUG_THIS_FILE )
    #if defined(CUL_COMPILER_MSVC)
        #pragma optimize( "", on )
    #elif defined( CUL_COMPILER_CLANG)
        #pragma clang optimize on
    #elif defined( CUL_COMPILER_GCC)
        #pragma GCC pop_options
    #endif
#endif  // #if defined(DEBUG_THIS_FILE)

#ifdef _MSC_VER
#pragma warning( pop )
#endif