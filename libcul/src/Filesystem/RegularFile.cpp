#include "CUL/Filesystem/RegularFile.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

using namespace CUL::FS;
using String = const CUL::String;

RegularFile::RegularFile( const String& path, CULInterface* interface ) : IFile( path, interface ), m_path( path )
{
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

void RegularFile::overwriteContents( const CUL::String& value )
{
    CUL::String valueCopy = value;

    m_rows.clear();
    m_rowsAsChars.clear();
    m_cached.clear();

    const bool hasCarriage = valueCopy.find( '\r' ) != -1;
    if( hasCarriage )
    {
        valueCopy.removeAll( '\r' );
    }

    m_rows = valueCopy.split( '\n' );
    cacheFile();
}

void RegularFile::load( bool keepLineEndingCharacter, bool removeBottomEmptyLines )
{
    CUL::Assert::check( exists(), "Cannot open the file: %s", m_path.getPath().cStr() );

    m_rows.clear();
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    m_removeBottomEmptyLines = removeBottomEmptyLines;
    std::ifstream infile;
    infile.open( m_path.getPath().cStr(), std::ios_base::in );
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
        for(std::int32_t i = rowsCount - 1; i >= 0; --i)
        {
            String& row = m_rows[static_cast<std::size_t>( i )];
            if( row == "\n" || row.empty() || row == "\r\n" )
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

const String& RegularFile::firstLine() const
{
    return m_rows.front();
}

const String& RegularFile::lastLine() const
{
    return m_rows.back();
}

const String& RegularFile::getAsOneString() const
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
        m_cached.append( line );
        if( line.find( '\n' ) == -1 && line.find( "\r\n" ) == -1 )
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

void RegularFile::loadFromString( const String& contents, bool keepLineEndingCharacter /*= false */ )
{
    m_cached = contents;
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    const std::vector<String> lines = m_cached.split( "\n" );
    for( const auto& line : lines )
    {
        m_rows.emplace_back( line );
        m_rowsAsChars.push_back( m_rows.back().cStr() );
    }
}

void RegularFile::loadFromStringNoEmptyLines( const String& contents, bool keepLineEndingCharacter /*= false */ )
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

    initializeRowsChar();
}

void RegularFile::initializeRowsChar()
{
    for( const auto& line : m_rows )
    {
        m_rowsAsChars.push_back( line.cStr() );
    }
}

void RegularFile::addLine( const String& line )
{
    m_rows.push_back( line );
    cacheFile();
}

void RegularFile::saveFile()
{
    auto pathString = m_path.getPath().getString();
    std::ofstream file( pathString );
    const size_t rowsCount = m_rows.size();
    for( size_t i = 0; i < rowsCount; ++i )
    {
        const String& line = m_rows[i];
        if( line.empty() )
        {
            file << '\n';
        }
        else
        {
            file << line.cStr() << "\n";
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
