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
    m_currentFilePath = m_files.begin();
}

void FileDatabase::loadFilesFromDatabase( const Path& inPath )
{
    m_databasePath = inPath;
    loadFilesFromDatabase();
}

void FileDatabase::loadFilesFromDatabase()
{
    initDb();

    std::string sqlQuery = std::string( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES" );
    auto callback = []( void* thisPtrValue, int, char** argv, char** )
    {
        auto thisPtr = reinterpret_cast<FileDatabase*>( thisPtrValue );
        const bool newWay = true;
        Path fileAsPath = argv[0];

        FileInfo fi;
        fi.MD5 = argv[2];
        fi.FilePath = argv[0];
        fi.Size = argv[1];
        fi.ModTime = argv[3];
        thisPtr->addFileToCache( fi );

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

void FileDatabase::initDb()
{
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
        LAST_MODIFICATION varchar(1024)\
        );";
        std::string errorResult( zErrMsg );
        rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, 0, &zErrMsg );
    }
}

void FileDatabase::addFileToCache( const Path& path )
{
    addFile( path.getMd5(), path.getPath(), CUL::String( (unsigned)path.getFileSize() ), path.getLastModificationTime().toString() );
}

void FileDatabase::addFileToCache( const FileInfo& path )
{
    {
        std::lock_guard<std::mutex> guard( m_filesMtx );
        m_files.push_back( path );
    }
}

void FileDatabase::addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime )
{
    if( filePath.contains( "w klimacie post apokaliptycznym Science Fictio" ) || filePath.contains( "mietnik" ) )
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

    if( false )
    {
        auto fileInfo = getFileFromDB( filePath );
        LOG::ILogger::getInstance()->log( fileInfo.FilePath.getPath() );
    }

    FileInfo fi;
    fi.MD5 = md5;
    fi.ModTime = modTime;
    fi.FilePath = filePath;
    fi.Size = fileSize;

    addFileToCache( fi );
}

FileDatabase::FileInfo FileDatabase::getFileFromDB( const String& path ) const
{
    FileDatabase::FileInfo result;

    String sqlQuery =
        "SELECT * \
FROM FILES \
WHERE PATH='" + path + "';";

    const char* queryAsCharPtr = sqlQuery.cStr();
    auto callback = [] ( void* fileInfoPtr, int argc, char** argv, char** info ){
        const char* path = argv[0];
        std::wstring asWstring = FS::s2ws( path, CP_ACP );


        FileDatabase::FileInfo* fileInfoFromPtr = reinterpret_cast<FileDatabase::FileInfo*>( fileInfoPtr );
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

void FileDatabase::removeFilesThatDoesNotExist()
{
    std::list<String> filesToRemove;

    {
        std::lock_guard<std::mutex> guard( m_filesMtx );
        for( const auto& file : m_files )
        {
            if( !file.FilePath.exists() )
            {
                filesToRemove.push_back( file.FilePath.getPath() );
            }
        }
    }

    for( const auto& file : filesToRemove )
    {
        removeFileFromDB( file );
    }
}

void FileDatabase::removeFileFromDB( const CUL::String& path )
{
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

    {
        std::lock_guard<std::mutex> guard( m_filesMtx );
        auto it = std::find_if( m_files.begin(), m_files.end(),
                                [path] ( const FileInfo& curr )                            {
            return curr.FilePath == path;
        } );

        if( it != m_files.end() )
        {
            m_files.erase( it );
        }
    }
}

const FileDatabase::FileInfo* FileDatabase::getFileInfo( const CUL::String& path ) const
{
    const FileDatabase::FileInfo* result = nullptr;
    {
        std::lock_guard<std::mutex> guard( m_filesMtx );
        auto it = std::find_if( m_files.begin(), m_files.end(),
                                [path] ( const FileInfo& curr ){
            return curr.FilePath == path;
        } );
        if( it != m_files.end() )
        {
            result = &*it;
        }
    }

    return result;
}

void FileDatabase::removeFilesThatDoNotExistFromBase()
{
    std::list<FileInfo>::iterator it;

    {
        std::lock_guard<std::mutex> guard( m_filesMtx );
        it = m_files.begin();
    }

    if( it == m_files.end() )
    {
        return;
    }

    while( true )
    {
        FileInfo fileInfo = *it;
        {
            std::lock_guard<std::mutex> guard( m_filesMtx );
            ++it;
        }
        

        if( !fileInfo.FilePath.exists() )
        {
            LOG::ILogger::getInstance()->log( String( "File [" ) + fileInfo.FilePath.getPath().getString() + String( "] has not been found on disk. Deleting from base." ) );
            removeFileFromDB( fileInfo.FilePath );
        }

        {
            std::lock_guard<std::mutex> guard( m_filesMtx );
            if( it == m_files.end() )
            {
                break;
            }
        }
    }
}

std::list<FileDatabase::FileInfo>::iterator FileDatabase::getNextFile()
{
    std::lock_guard<std::mutex> guard( m_filesMtx );
    std::list<FileDatabase::FileInfo>::iterator result;
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

#ifdef _MSC_VER
#pragma warning( pop )
#endif