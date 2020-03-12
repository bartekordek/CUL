#include "FileRegularImpl.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

using namespace CUL::FS;
using CsStr = const CUL::String;

FileRegularImpl::FileRegularImpl()
{
    std::cout << "FileRegularImpl::FileRegularImpl() " << this << "\n";
}

void FileRegularImpl::changePath( const Path& newPath )
{
    m_path = newPath;
}

const Path& FileRegularImpl::getPath() const
{
    return m_path;
}

void FileRegularImpl::reload( Cbool keepLineEndingCharacter )
{
    unload();
    load( keepLineEndingCharacter );
}

void FileRegularImpl::load( Cbool keepLineEndingCharacter )
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

CsStr& FileRegularImpl::firstLine() const
{
    return rows.front();
}

CsStr& FileRegularImpl::lastLine() const
{
    return rows.back();
}

CsStr& FileRegularImpl::getAsOneString() const
{
    return m_cached;
}

void FileRegularImpl::cacheFile()
{
    m_cached = "";
    for( const auto& line : rows )
    {
        m_cached += line;
        m_cached += "\n";
        m_rowsAsChars.push_back( const_cast<char*>( line.cStr() ) );
    }
}

const FileType FileRegularImpl::getType() const
{
    return FileType::TXT;
}

Cunt FileRegularImpl::getLinesCount() const
{
    return static_cast<Cunt>( rows.size() );
}

const char** FileRegularImpl::getContent() const
{
    return const_cast<const char**>( &m_rowsAsChars[0] );
}


FileRegularImpl::~FileRegularImpl()
{
    std::cout << "FileRegularImpl::~FileRegularImpl() " << this << "\n";
}