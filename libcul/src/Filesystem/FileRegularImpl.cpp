#include "FileRegularImpl.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

using namespace CUL::FS;
using String = const CUL::String;

FileRegularImpl::FileRegularImpl( const String& path, CULInterface* interface ):
    IFile( path, interface ),
    m_path( path )
{
}

void FileRegularImpl::changePath( const Path& newPath )
{
    m_path = newPath;
    IFile::setPath( newPath );
}

const Path& FileRegularImpl::getPath() const
{
    return m_path;
}

void FileRegularImpl::reload( bool keepLineEndingCharacter )
{
    unload();
    load( keepLineEndingCharacter );
}

void FileRegularImpl::reload()
{
    unload();
    load( m_keepLineEndingCharacter );
}

void FileRegularImpl::load( bool keepLineEndingCharacter )
{
    CUL::Assert::simple( exists(), "Cannot open the file: " + m_path.getPath() );

    m_rows.clear();
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

        m_rows.push_back( line );
    }
    infile.close();

    cacheFile();
}

void FileRegularImpl::unload()
{
    m_rows.clear();
    m_cached = "";
}

const String& FileRegularImpl::firstLine() const
{
    return m_rows.front();
}

const String& FileRegularImpl::lastLine() const
{
    return m_rows.back();
}

const String& FileRegularImpl::getAsOneString() const
{
    return m_cached;
}

void FileRegularImpl::cacheFile()
{
    if( getIsCacheEnabled() == false )
    {
        return;
    }

    m_cached = "";
    for( const auto& line : m_rows )
    {
        m_cached += line;
        m_cached += "\n";
        m_rowsAsChars.push_back( const_cast<char*>( line.cStr() ) );
    }
}

FileType FileRegularImpl::getType() const
{
    return FileType::TXT;
}

void FileRegularImpl::loadFromString( const String& contents, bool keepLineEndingCharacter /*= false */ )
{
    m_cached = contents;
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    const std::vector<String> lines = m_cached.split( "\n" );
    for( const auto& line : lines )
    {
        m_rows.emplace_back( line );
        m_rowsAsChars.push_back(m_rows.back().cStr());
    }
}

void FileRegularImpl::loadFromStringNoEmptyLines( const String& contents, bool keepLineEndingCharacter /*= false */ )
{
    m_cached.clear();
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    std::vector<String> lines = contents.split( "\n" );
    for( String& line : lines )
    {
        if( line.empty() )
        {
            continue;
        }

        if( keepLineEndingCharacter )
        {
            line += String( "\n" );
        }

        m_rows.emplace_back( line );
        m_cached += line;
    }

    for( const auto& line : m_rows )
    {
        m_rowsAsChars.push_back( line.cStr() );
    }
}

void FileRegularImpl::addLine( const String& line )
{
    m_rows.push_back( line );
    cacheFile();
}

void FileRegularImpl::saveFile()
{
    auto pathString = m_path.getPath().getString();
    std::ofstream file( pathString );
    const size_t rowsCount = m_rows.size();
    for( size_t i = 0; i < rowsCount; ++i )
    {
        const String& line = m_rows[i];
        file << line.cStr() << "\n";
    }
    file.close();
}

unsigned FileRegularImpl::getLinesCount() const
{
    return static_cast<unsigned>( m_rows.size() );
}

const char** FileRegularImpl::getContent() const
{
    return const_cast<const char**>( &m_rowsAsChars[0] );
}


FileRegularImpl::~FileRegularImpl()
{
}