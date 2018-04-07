#include "FileRegularImpl.hpp"

#define BOOST_CONFIG_SUPPRESS_OUTDATED_MESSAGE
#include <boost/filesystem.hpp>
#include <boost/filesystem/path.hpp>

#include <iostream>

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

IFile& FileRegularImpl::operator=( const std::string& rPath )
{
    this->path = rPath;
    reload();
    return *this;
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
            false == line.empty() && // Skip empty line
                ( 
                    line.back() == ( '\r' ) || 
                    line.back() == ( '\n' ) ) )
        {
            line.pop_back();
        }
        line += '\n';
        this->rows.push_back( line );
    }
    infile.close();

    cacheFile();
}

void FileRegularImpl::unload()
{
    this->rows.clear();
    this->m_cached = "";
}

const std::string& FileRegularImpl::firstLine()const
{
    return this->rows.front();
}

const std::string& FileRegularImpl::lastLine()const
{
    return this->rows.back();
}

const std::string& FileRegularImpl::getAsOneString()const
{
    return this->m_cached;
}

void FileRegularImpl::cacheFile()
{
    this->m_cached = "";
    for( const auto& line: this->rows )
    {
        this->m_cached += line;
        this->m_cached += "\n";

        
        this->m_rowsAsChars.push_back( const_cast<char*>( line.c_str() ) );
    }
}

cunt FileRegularImpl::getLinesCount()const
{
    return static_cast< cunt >( this->rows.size() );
}

const char** FileRegularImpl::getContent()const
{
    return const_cast<const char**>( &this->m_rowsAsChars[ 0 ] );
}