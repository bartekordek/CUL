#include "CUL/Filesystem/FileDatabase.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Log/ILogger.hpp"
#include "Filesystem/FSUtils.hpp"
#include "CUL/CULInterface.hpp"

#include "CUL/IMPORT_sqlite3.hpp"

//5039

#ifdef _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 1404 )
#endif

using namespace CUL;
using namespace FS;

static FileDatabase* g_dbInstance = nullptr;

bool FileDatabase::FileInfo::operator==( const FileInfo& second ) const
{
    return ( Size == second.Size ) && ( MD5 == second.MD5 );
}

FileDatabase::FileDatabase()
{
}

std::vector<String> FileDatabase::loadFilesFromDatabase( const Path& inPath )
{
    m_databasePath = inPath;
    return loadFilesFromDatabase();
}

struct ListAndApi
{
    FileDatabase* thisPtr = nullptr;
    std::vector<String> FilesList;
    std::vector<String> RemoveList;
    CUL::FS::FSApi* FS_API = nullptr;
    std::atomic<int64_t>* m_currentFileIndex = nullptr;
};

float FileDatabase::getPercentage() const
{
    return 100.f * m_current / ( 1.f * m_rowCount );
}

CUL::String FileDatabase::getDbState() const
{
    CUL::String result;
    {
        std::lock_guard<std::mutex> lock( m_dbStateMtx );
        result = m_dbState;
    }

    return result;
}

std::vector<String> FileDatabase::loadFilesFromDatabase()
{
    std::vector<String> result;

    initDb();

    ListAndApi removeData;
    removeData.thisPtr = this;
    removeData.FS_API = CUL::CULInterface::getInstance()->getFS();
    removeData.m_currentFileIndex = &m_current;

    CUL::FS::FSApi* fsApi = CUL::CULInterface::getInstance()->getFS();

    std::string sqlQuery = std::string( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES" );
    auto callback = []( void* thisPtrValue, int, char** argv, char** )
    {
        auto rd = reinterpret_cast<ListAndApi*>( thisPtrValue );
        String file = argv[0];
        rd->FilesList.push_back( file );
        ++*rd->m_currentFileIndex;

        float per = rd->thisPtr->getPercentage();
        const CUL::String stat = "loadFilesFromDatabase -> load files list... " + CUL::String( per );

        return 0;
    };

    setDBstate( "loadFilesFromDatabase -> get file count..." );
    m_rowCount = getFileCount();
    setDBstate( "loadFilesFromDatabase -> get file count... done." );

    char* zErrMsg = nullptr;
    setDBstate( "loadFilesFromDatabase -> load files list..." );
    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, &removeData, &zErrMsg );
    setDBstate( "loadFilesFromDatabase -> load files list... done." );

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
        setDBstate( "loadFilesFromDatabase -> deleting remnants..." );
        size_t filesCount = removeData.FilesList.size();

        setDBstate( "loadFilesFromDatabase -> deleting remnants... collecting not existing files..." );
        for( size_t i = 0; i < filesCount; ++i )
        {
            const float perc = 100.f * ( i + 1 ) / ( 1.f * filesCount );

            if( !fsApi->fileExist( removeData.FilesList[i] ) )
            {
                removeData.RemoveList.push_back( removeData.FilesList[i] );
            }

            setDBstate( "loadFilesFromDatabase -> deleting remnants... collecting not existing files..." + CUL::String( perc ) );
        }
        setDBstate( "loadFilesFromDatabase -> deleting remnants... collecting not existing files... done." );

        filesCount = removeData.RemoveList.size();
        size_t groups = ( filesCount < 32)? 1: filesCount / 2;

        const size_t filesPerGroup = filesCount / groups;

        std::vector<CUL::String> filesToDelete;
        size_t groupCounter = 0;
        setDBstate( "loadFilesFromDatabase -> deleting remnants... removing from db..." );
        for( size_t i = 0; i < filesCount; ++i )
        {
            const float perc = 100.f * ( i + 1 ) / ( 1.f * filesCount );

            filesToDelete.push_back( removeData.RemoveList[i] );

            ++groupCounter;

            if( groupCounter >= filesPerGroup )
            {
                groupCounter = 0;
                removeFilesFromDb( filesToDelete );
                filesToDelete.clear();
            }

            setDBstate( "loadFilesFromDatabase -> deleting remnants... removing from db..." + CUL::String( perc ) );
        }
        setDBstate( "loadFilesFromDatabase -> deleting remnants... removing from db... done." );

        //setDBstate( "loadFilesFromDatabase -> deleting remnants... " + CUL::String( perc ) );

        setDBstate( "loadFilesFromDatabase -> deleting remnants... done." );
    }

    setDBstate( "loadFilesFromDatabase -> finished." );

    return result;
}

std::list<CUL::String> FileDatabase::getFilesMatching( const CUL::String& fileSize, const CUL::String& md5 ) const
{
    std::list<CUL::String> result;
    CUL::String sqlQuery = CUL::String( "SELECT PATH FROM FILES WHERE ( SIZE='" ) + fileSize + "' AND MD5='" + md5 + "');";

    char* zErrMsg = nullptr;
    auto callback = [] ( void* voidValue, int argc, char** argv, char** info ){
        std::list<CUL::String>* resultPtr = reinterpret_cast<std::list<CUL::String>*>( voidValue );
        resultPtr->push_back( CUL::String( argv[0] ) );
        return 0;
    };

    std::string sqlQuerySTR = sqlQuery.string();
    int rc = sqlite3_exec( m_db, sqlQuerySTR.c_str(), callback, &result, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::simple( false, "DB ERROR!" );
    }

    return result;
}

int64_t FileDatabase::getFileCount() const
{
    int64_t result = 0;

    char* zErrMsg = nullptr;
    //std::string sqlQuery = std::string( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES" );
    std::string sqlQuery = std::string( "SELECT COUNT(PATH) as something from FILES" );
    auto callback = [] ( void* voidPtr, int, char** argv, char** ){

        CUL::String valueAsString = argv[0];
        int64_t* resulPtr = reinterpret_cast<int64_t*>( voidPtr );
        *resulPtr = valueAsString.toInt64();

        return 0;
    };

    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, &result, &zErrMsg );


    if( rc != SQLITE_OK )
    {
        std::string errMessage = zErrMsg;
        CUL::Assert::simple( false, "DB ERROR: " + errMessage );
    }


    return result;
}

void FileDatabase::initDb()
{
    setDBstate( "Initi db..." );
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
        PATH varchar(1024),\
        SIZE varchar(512),\
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
    else
    {

    }
    setDBstate( "Initi db... done." );
}

void FileDatabase::addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime )
{
    const CUL::String filePathNormalized = sanitize( filePath );
    auto foundFile = getFileInfo( filePath );
    char* zErrMsg = nullptr;
    auto callback = [] ( void*, int, char**, char** ){
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    CUL::String sqlQuery = "";
    if( foundFile.Found )
    {
        sqlQuery = "UPDATE FILES SET SIZE='" + fileSize + "', LAST_MODIFICATION='" + modTime + "' WHERE PATH='" + filePath + "'";
    }
    else
    {
        sqlQuery = "INSERT INTO FILES (PATH, SIZE, MD5, LAST_MODIFICATION ) VALUES ('" + filePathNormalized + "', '" + fileSize +
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
    FileDatabase::FileInfo result;
    auto filePathNormalized = sanitize( path );

    String sqlQuery =
        "SELECT * \
FROM FILES \
WHERE PATH='" + filePathNormalized + "';";

    const char* queryAsCharPtr = sqlQuery.cStr();
    auto callback = [] ( void* fileInfoPtr, int argc, char** argv, char** info ){
        const char* path = argv[0];
#if defined(CUL_WINDOWS)
        std::wstring asWstring = FS::s2ws( path, CP_ACP );
#else
        std::string asWstring = path;
#endif

        FileDatabase::FileInfo* fileInfoFromPtr = reinterpret_cast<FileDatabase::FileInfo*>( fileInfoPtr );
        fileInfoFromPtr->Found = true;
        fileInfoFromPtr->MD5 = argv[2];
        fileInfoFromPtr->Size = argv[1];
        fileInfoFromPtr->ModTime = argv[3];
        fileInfoFromPtr->FilePath = asWstring;

        return 0;
    };
    char* zErrMsg = nullptr;

    int rc = sqlite3_exec( m_db, sqlQuery.cStr(), callback, &result, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        std::string errMessage = zErrMsg;
        CUL::Assert::simple( false, "DB ERROR: " + errMessage );
    }

    return result;
}

void FileDatabase::removeFileFromDB( const CUL::String& pathRaw )
{
    auto path = sanitize( pathRaw );

    std::string sqlQuery = std::string( "DELETE FROM FILES WHERE PATH='" ) + path.string() + "';";

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
    const size_t pathsSize = paths.size();

    CUL::String pathsListed = "( '";
    for( size_t i = 0; i < pathsSize - 1; ++i )
    {
        auto pathSanitized = sanitize( paths[i] );
        pathsListed += pathSanitized + "', '";
    }
    pathsListed += sanitize( paths[pathsSize-1] ) + "')";

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

void FileDatabase::setDBstate( const CUL::String& state )
{
    std::lock_guard<std::mutex> lock( m_dbStateMtx );
    m_dbState = state;
}

FileDatabase::~FileDatabase()
{
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

#ifdef _MSC_VER
#pragma warning( pop )
#endif