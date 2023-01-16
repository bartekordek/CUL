#include "CUL/Filesystem/FileDatabase.hpp"
#include "CUL/Filesystem/FSApi.hpp"

#include "CUL/CULInterface.hpp"

#include "CUL/IMPORT_sqlite3.hpp"

using namespace CUL;
using namespace FS;

static FileDatabase* g_dbInstance = nullptr;

FileDatabase::FileDatabase()
{
    m_currentFilePath = m_files.begin();
}

void FileDatabase::setTargetDatabasePath( const Path& inPath )
{
	m_databasePath = inPath;
}

void FileDatabase::addSearchPaths( const std::vector<Path>& searchPaths )
{
	m_searchPaths = searchPaths;
}

void FileDatabase::search( bool runConstantly )
{
    g_dbInstance = this;

    int rc = sqlite3_open( m_databasePath.getPath().cStr(), &m_db );

    m_worker.addTask( [this] (){
        addFilesFromDB();
        removeFilesThatDoesNotExist();
    } );

	m_worker.addTask( [this] (){
        for( const auto& path : m_searchPaths )
        {
            auto culFF = CUL::CULInterface::getInstance()->getFS();

            culFF->ListAllFiles( path, [this] ( const CUL::FS::Path& path ){
                if( !path.getIsDir() )
                {
                    addFileToDb( path );
                    addFileToDbCache( path );
                }
            } );
        }
	} );

    m_worker.setRemoveTasksWhenConsumed( !runConstantly );
    m_worker.setThreadName( "MainFileDBWorker" );
    m_worker.run();
}

void FileDatabase::addFilesFromDB()
{
    std::string sqlQuery = std::string( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES" );
    auto callback = [] ( void* thisPtrValue, int, char** argv, char** ){
        auto thisPtr = reinterpret_cast<FileDatabase*>( thisPtrValue );
        const bool newWay = true;
        Path fileAsPath = argv[0];

        if( fileAsPath.exists() )
        {
            if( newWay )
            {
                thisPtr->addFileToDbCache( fileAsPath );

            }
            else
            {
                thisPtr->addFile( argv[2], argv[0], argv[1], argv[3] );
            }
        }

        return 0;
    };

    char* zErrMsg = nullptr;
    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, this, &zErrMsg );

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

void FileDatabase::fetchFile( const Path& path )
{
    std::lock_guard<std::mutex> guard( m_filesMtx );
    auto it = std::find_if( m_files.begin(), m_files.end(), [path] ( const Path& curr ){
        return curr.getPath() == path;
    } );

    if( it != m_files.end() )
    {
    }
}

void FileDatabase::addFileToDb( const Path& path )
{
    addFile( path.getMd5(), path.getPath(), CUL::String( (unsigned) path.getFileSize() ), path.getLastModificationTime().toString() );
}

void FileDatabase::addFileToDbCache( const Path& path )
{
    {
        std::lock_guard<std::mutex> guard( m_filesMtx );
        m_files.push_back( path );
    }
    FoundFileDelegate.execute( path );
}

void FileDatabase::addFileToDbCache( const String& path, const String& md5, const String& size, const String& modtime )
{
    Path pathValue;
    pathValue = path;
    pathValue.setFileSize( size.toUInt() );
    pathValue.setMd5( md5 );
    pathValue.setModTime( modtime );

    addFileToDbCache( pathValue );
}

void FileDatabase::addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime )
{
    if( filePath.contains( "science_in_this_shit" ) )
    {
        auto x = 0;
    }

    CUL::String result;
    CUL::String filePathNormalized = filePath;
    filePathNormalized.replace( "./", "" );
    filePathNormalized.replace( "'", "''" );
    filePathNormalized.removeAll( '\0' );
    CUL::String sqlQuery = "INSERT INTO FILES (PATH, SIZE, MD5, LAST_MODIFICATION ) VALUES ('" + filePathNormalized + "', '" + fileSize +
        "', '" + md5 + "', '" + modTime + "');";

    char* zErrMsg = nullptr;
    auto callback = [] ( void*, int, char**, char** )    {
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

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

void FileDatabase::initDb()
{
    auto callback = [] ( void*, int, char**, char** )    {
        // DuplicateFinder::s_instance->callback(NotUsed, argc, argv, azColName);
        return 0;
    };

    char* zErrMsg = nullptr;

    std::string sqlQuery =
        "CREATE TABLE FILES (\
    PATH varchar(1024),\
    SIZE varchar(512),\
    MD5 varchar(1024),\
    LAST_MODIFICATION varchar(1024)\
    );";
    
    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, 0, &zErrMsg );
    if( rc != SQLITE_OK )
    {
        std::string errorResult( zErrMsg );
        CUL::Assert::simple( false, "DB ERROR!" );
    }
}

void FileDatabase::removeFilesThatDoesNotExist()
{
    std::list<String> filesToRemove;

    {
        std::lock_guard<std::mutex> guard( m_filesMtx );
        for( const auto& file: m_files )
        {
            if( !file.exists() )
            {
                filesToRemove.push_back( file );
            }
        }
    }

    for( const auto& file: filesToRemove )
    {
        removeFileFromDBCache( file );
        removeFileFromDB( file );
    }
}

void FileDatabase::removeFileFromDB( const CUL::String& path )
{
    std::string sqlQuery = std::string( "DELETE FROM FILES WHERE PATH='" ) + path.string() + "';";

    char* zErrMsg = nullptr;
    auto callback = [] ( void* thisPtrValue, int, char**, char** ){
        auto thisPtr = reinterpret_cast<FileDatabase*>( thisPtrValue );
        // DuplicateFinder::s_instance->callback( NotUsed, argc, argv, azColName );
        return 0;
    };

    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, this, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::simple( false, "DB ERROR!" );
    }
}

void FileDatabase::removeFileFromDBCache( const CUL::String& path )
{
    std::lock_guard<std::mutex> guard( m_filesMtx );
    auto it = std::find_if( m_files.begin(), m_files.end(), [path] ( const Path& curr ){
        return curr.getPath() == path;
    } );

    if( it != m_files.end() )
    {
        m_files.erase( it );
    }
}

std::list<Path>::iterator FileDatabase::getNextFile()
{
    std::lock_guard<std::mutex> guard( m_filesMtx );
    std::list<Path>::iterator result;
    if( m_currentFilePath == m_files.end() )
    {
        m_currentFilePath = m_files.begin();
    }

    result = m_currentFilePath;
    ++result;

    return result;
}

FileDatabase::~FileDatabase()
{
    sqlite3_close( m_db );
}