#pragma once

#include "CUL/GenericUtils/DelegateTemplate.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/Threading/Worker.hpp"

#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_list.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

struct sqlite3;

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

class CULLib_API FileDatabase final
{
public:
	using MD5Value = String;

	FileDatabase();
	void setTargetDatabasePath( const Path& inPath );
	void addSearchPaths( const std::vector<Path>& searchPaths );

	void search( bool runConstantly );

	void addFile( MD5Value md5, const CUL::String& filePath, const CUL::String& fileSize, const CUL::String& modTime );
	void fetchFile( const Path& path );
	void addFileToDb( const Path& path );
	void addFileToDbCache( const Path& path );
	void addFileToDbCache( const String& path, const String& md5, const String& size, const String& modtime );

	void removeFileFromDB( const CUL::String& path );
	void removeFileFromDBCache( const CUL::String& path );

	std::list<Path>::iterator getNextFile();

	~FileDatabase();

	CUL::GUTILS::DelegateTemplateOneParam<String> FoundFileDelegate;
protected:
private:
	
	void addFilesFromDB();
	void initDb();
	void removeFilesThatDoesNotExist();
	
	sqlite3* m_db = nullptr;
	Path m_databasePath;
	std::vector<Path> m_searchPaths;

	std::mutex m_filesMtx;
	std::list<Path> m_files;

	Worker m_worker;
	String m_currentFile;

	std::list<Path>::iterator m_currentFilePath;

private:
	FileDatabase( const FileDatabase& rhv ) = delete;
	FileDatabase( const FileDatabase&& rhv ) = delete;
	FileDatabase& operator=( const FileDatabase& rhv ) = delete;
	FileDatabase& operator=( FileDatabase&& rhv ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )