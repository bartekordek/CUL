#include "CUL/Filesystem/RegularFile.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/String/StringUtil.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

using namespace CUL::FS;
using StringWr = const CUL::StringWr;

RegularFile::RegularFile( const StringWr& path, CULInterface* inInterface ): IFile( path, inInterface )
{
    m_path.createFrom( path );
}

void RegularFile::changePath( const Path& newPath )
{
    m_path = newPath;
    IFile::setPath( newPath );
}

const Path& RegularFile::getPath() const
{
    return m_path;
}

void RegularFile::reload( bool keepLineEndingCharacter )
{
    unload();
    load( keepLineEndingCharacter, m_removeBottomEmptyLines );
}

void RegularFile::reload()
{
    unload();
    load( m_keepLineEndingCharacter, m_removeBottomEmptyLines );
}

void RegularFile::overwriteContents( const CUL::StringWr& value )
{
    CUL::StringWr valueCopy = value;

    m_rows.clear();
    m_rowsAsChars.clear();
    m_cached.clear();

    valueCopy.removeAll( '\r' );

    m_rows = valueCopy.split( '\n' );
    cacheFile();
}

void RegularFile::load( bool keepLineEndingCharacter, bool removeBottomEmptyLines )
{
    const auto stdString = m_path.getPath().getSTDString();
    CUL::Assert::check( exists(), "Cannot open the file: %s", stdString.c_str() );

    m_rows.clear();
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    m_removeBottomEmptyLines = removeBottomEmptyLines;
    std::ifstream infile;
    infile.open( stdString.c_str(), std::ios_base::in );
    std::string line;
    while( std::getline( infile, line ) )
    {
        if( false == line.empty() &&  // Skip empty line
            ( line.back() == ( '\r' ) || line.back() == ( '\n' ) ) )
        {
            line.pop_back();
        }
        if( true == m_keepLineEndingCharacter )
        {
            line += '\n';
        }

        m_rows.emplace_back( line );
    }
    infile.close();

    if( m_removeBottomEmptyLines )
    {
        const std::int32_t rowsCount = static_cast<std::int32_t>( m_rows.size() );
        for( std::int32_t i = rowsCount - 1; i >= 0; --i )
        {
            StringWr& row = m_rows[static_cast<std::size_t>( i )];
            if( row.equals( "\n" ) || row.empty() || row.equals( "\r\n" ) )
            {
                m_rows.erase( m_rows.begin() + i );
            }
            else
            {
                break;
            }
        }
    }

    cacheFile();
}

void RegularFile::unload()
{
    m_rows.clear();
    m_cached = "";
}

const StringWr& RegularFile::firstLine() const
{
    return m_rows.front();
}

const StringWr& RegularFile::lastLine() const
{
    return m_rows.back();
}

const StringWr& RegularFile::getAsOneString() const
{
    return m_cached;
}

void RegularFile::cacheFile()
{
    if( getIsCacheEnabled() == false )
    {
        return;
    }

    m_cached = "";
    for( const auto& line : m_rows )
    {
        m_cached.append( line.getValue() );
        if( !line.contains( '\n' ) && line.find( "\r\n" ) == -1 )
        {
            m_cached.append( '\n' );
        }
    }

    initializeRowsChar();
}

FileType RegularFile::getType() const
{
    return FileType::TXT;
}

void RegularFile::loadFromString( const StringWr& contents, bool keepLineEndingCharacter /*= false */ )
{
    m_cached = contents;
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    const std::vector<StringWr> lines = m_cached.split( '\n' );
    for( const auto& line : lines )
    {
        m_rows.emplace_back( line );
        const char* duplicated = StringUtil::strdup( m_rows.back().getUtfChar() );
        m_rowsAsChars.push_back( duplicated );
    }
}

void RegularFile::loadFromStringNoEmptyLines( const StringWr& contents, bool keepLineEndingCharacter /*= false */ )
{
    m_cached.clear();
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    std::vector<StringWr> lines = contents.split( '\n' );
    for( StringWr& line : lines )
    {
        if( line.empty() )
        {
            continue;
        }

        if( keepLineEndingCharacter )
        {
            line += StringWr( "\n" );
        }

        m_rows.emplace_back( line );
        m_cached += line;
    }

    initializeRowsChar();
}

void RegularFile::initializeRowsChar()
{
    for( const auto& line : m_rows )
    {
        const std::string str = line.getSTDString();
        m_rowsAsChars.push_back( str.c_str() );
    }
}

void RegularFile::addLine( const StringWr& line )
{
    m_rows.push_back( line );
    cacheFile();
}

void RegularFile::saveFile()
{
    std::ofstream file( m_path.getPath().getUtfChar() );
    const size_t rowsCount = m_rows.size();
    for( size_t i = 0; i < rowsCount; ++i )
    {
        const StringWr& line = m_rows[i];
        if( line.empty() )
        {
            file << '\n';
        }
        else
        {
            file << line.getUtfChar() << "\n";
        }
    }
    file.close();
}

unsigned RegularFile::getLinesCount() const
{
    return static_cast<unsigned>( m_rows.size() );
}

const char** RegularFile::getContent() const
{
    return const_cast<const char**>( &m_rowsAsChars[0] );
}

RegularFile::~RegularFile()
{
}
