#include "FileRegularImpl.hpp"
#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>
using namespace CUL;
using namespace FS;

FileRegularImpl::FileRegularImpl()
{
}

FileRegularImpl::FileRegularImpl( const FileRegularImpl& file ):
    path( file.path )
{
}

FileRegularImpl::FileRegularImpl( const std::string& filePath ):
    path( filePath )
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
    std::ifstream infile;
    infile.open( 
        this->path.getPath(), 
        std::ios_base::in );
    std::string line;
    while( std::getline( infile, line ) )
    {
        if(
            false == line.empty() && 
                ( 
                    line.back() == ( '\r' ) || 
                    line.back() == ( '\n' ) ) )
        {
            line.pop_back();
        }
    this->rows.push_back( line );
    }
    infile.close();
}

void FileRegularImpl::unload()
{
    this->rows.clear();
}

const std::string& FileRegularImpl::firstLine()const
{
    return this->rows.front();
}

const std::string& FileRegularImpl::lastLine()const
{
    return this->rows.back();
}