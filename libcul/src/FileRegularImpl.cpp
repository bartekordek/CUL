#include "FileRegularImpl.hpp"

#include "BoostFilesystem.hpp"
#include "CUL/STD_iostream.hpp"

using namespace CUL;
using namespace FS;

FileRegularImpl::FileRegularImpl()
{
}

FileRegularImpl::FileRegularImpl( const FileRegularImpl& file ):
    m_path( file.m_path )
{
}

FileRegularImpl::FileRegularImpl( const Path& filePath ):
    m_path( filePath )
{

}

IFile& FileRegularImpl::operator=( const Path& rPath )
{
    changePath( rPath );
    return *this;
}

void FileRegularImpl::changePath( const Path& newPath )
{
    this->m_path = newPath;
}

FileRegularImpl::~FileRegularImpl()
{

}

const Path& FileRegularImpl::getPath()const
{
    return this->m_path;
}

const bool FileRegularImpl::exists()const
{
    return this->m_path.exists();
}

const bool FileRegularImpl::isBinary()const
{
    return true;//TODO: Implement
}

void FileRegularImpl::reload( CBool keepLineEndingCharacter )
{
    unload();
    load( keepLineEndingCharacter );
}

void FileRegularImpl::load( CBool keepLineEndingCharacter )
{
    this->rows.clear();
    this->m_keepLineEndingCharacter = keepLineEndingCharacter;
    std::ifstream infile;
    infile.open( 
        this->m_path.getPath(), 
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
        if( true == this->m_keepLineEndingCharacter )
        {
            line += '\n';
        }

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

CnstMyStr& FileRegularImpl::firstLine()const
{
    return this->rows.front();
}

CnstMyStr& FileRegularImpl::lastLine()const
{
    return this->rows.back();
}

CnstMyStr& FileRegularImpl::getAsOneString()const
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