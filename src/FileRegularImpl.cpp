#include "FileRegularImpl.hpp"
#include "CUL/ListFactory.hpp"
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
using namespace CUL;
using namespace FS;

FileRegularImpl::FileRegularImpl():
	rows( ListFactory::createVectorListPtr<std::string>() )
{
}

FileRegularImpl::FileRegularImpl( const FileRegularImpl& file ):
	path( file.path ),
	rows( ListFactory::createVectorListPtr<std::string>() )
{
}

FileRegularImpl::FileRegularImpl( const std::string& filePath ):
	path( filePath ),
	rows( ListFactory::createVectorListPtr<std::string>() )
{

}

FileRegularImpl::~FileRegularImpl()
{

}

Path* FileRegularImpl::getPath()
{
	return &this->path;
}

const bool FileRegularImpl::exists()const
{
	return this->path.exists();
}

const bool FileRegularImpl::isBinary()const
{
	return true;//TODO: Implement
}

void FileRegularImpl::reload()
{
	unload();
	load();
}

void FileRegularImpl::load()
{
	std::ifstream infile( this->path.getPath() );
	std::string line;
	while( std::getline( infile, line ) )
	{
		this->rows->pushBack( line );
	}
}

void FileRegularImpl::unload()
{
	this->rows->clear();
}

const IIterator<std::string>* FileRegularImpl::begin()const
{
	return &this->rows->begin();
}

const IIterator<std::string>* FileRegularImpl::end()const
{
	return &this->rows->end();
}

IIterator<std::string>* FileRegularImpl::getIt()
{
	return this->rows->getRandomIteratorPtr();
}

const IIterator<std::string>* FileRegularImpl::firstLine()const
{
	return &this->rows->firstElement();
}

const IIterator<std::string>* FileRegularImpl::lastLine()const
{
	return &this->rows->lastElement();
}