#include "FileRegularImpl.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

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
    m_path = newPath;
}

FileRegularImpl::~FileRegularImpl()
{

}

const Path& FileRegularImpl::getPath()const
{
    return m_path;
}

const bool FileRegularImpl::exists()const
{
    return m_path.exists();
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
    CUL::Assert::simple( exists(), "Cannot open the file: " + m_path.getPath() );

    rows.clear();
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    std::ifstream infile;
    infile.open( 
        m_path.getPath().cStr(), 
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
        if( true == m_keepLineEndingCharacter )
        {
            line += '\n';
        }

        rows.push_back( line );
    }
    infile.close();

    cacheFile();
}

void FileRegularImpl::unload()
{
    rows.clear();
    m_cached = "";
}

CsStr& FileRegularImpl::firstLine()const
{
    return rows.front();
}

CsStr& FileRegularImpl::lastLine()const
{
    return rows.back();
}

CsStr& FileRegularImpl::getAsOneString()const
{
    return m_cached;
}

void FileRegularImpl::cacheFile()
{
    m_cached = "";
    for( const auto& line: rows )
    {
        m_cached += line;
        m_cached += "\n";
        m_rowsAsChars.push_back( const_cast<char*>( line.cStr() ) );
    }
}

cunt FileRegularImpl::getLinesCount()const
{
    return static_cast< cunt >( rows.size() );
}

const char** FileRegularImpl::getContent()const
{
    return const_cast<const char**>( &m_rowsAsChars[ 0 ] );
}