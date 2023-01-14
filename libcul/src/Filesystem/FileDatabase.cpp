#include "CUL/Filesystem/FileDatabase.hpp"
#include "CUL/Filesystem/FSApi.hpp"

#include "CUL/CULInterface.hpp"

#include "CUL/IMPORT_sqlite3.hpp"

using namespace CUL;
using namespace FS;

static FileDatabase* g_dbInstance = nullptr;

void FileDatabase::setTargetDatabasePath( const Path& inPath )
{
	m_databasePath = inPath;
}

void FileDatabase::addSearchPaths( const std::vector<Path>& searchPaths )
{
	m_searchPaths = searchPaths;
}

void FileDatabase::startSearch()
{
    g_dbInstance = this;

    int rc = sqlite3_open( m_databasePath.getPath().cStr(), &m_db );


	m_worker.addTask( [this] (){
        for( const auto& path : m_searchPaths )
        {
            auto culFF = CUL::CULInterface::getInstance()->getFS();

            culFF->ListAllFiles( path, [this] ( const CUL::FS::Path& path ){
                std::lock_guard<std::mutex> guard( m_filesMtx );
                m_files.push_back( path );
            } );
        }
	} );
}

void FileDatabase::addFilesFromDB()
{
    std::string sqlQuery = std::string( "SELECT PATH, SIZE, MD5, LAST_MODIFICATION FROM FILES" );
    auto callback = [] ( void*, int /* argc */, char** argv, char** )    {
        //g_dbInstance->
        //s_instance->addForCheckForDeletionList( argv[0] );
        return 0;
    };

    char* zErrMsg = nullptr;
    int rc = sqlite3_exec( m_db, sqlQuery.c_str(), callback, 0, &zErrMsg );

    if( rc != SQLITE_OK )
    {
        CUL::Assert::simple( false, "DB ERROR!" );
    }
}