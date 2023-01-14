#pragma once

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
	FileDatabase() = default;
	void setTargetDatabasePath( const Path& inPath );
	void addSearchPaths( const std::vector<Path>& searchPaths );

	void startSearch();

	~FileDatabase() = default;
protected:
private:
	void addFilesFromDB();
	sqlite3* m_db = nullptr;
	Path m_databasePath;
	std::vector<Path> m_searchPaths;

	std::mutex m_filesMtx;
	std::list<Path> m_files;

	Worker m_worker;
	String m_currentFile;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )