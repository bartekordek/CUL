#include "CUL/Filesystem/RegularFile.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/String/StringUtil.hpp"

#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

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
    m_asOne.clear();
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
    m_asOne.clear();
    m_cached = contents;
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    const std::vector<StringWr> lines = m_cached.split( '\n' );
    for( const auto& line : lines )
    {
        m_rows.emplace_back( line );
    }
    initializeRowsChar();
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
    std::size_t charsUsed{ 0u };

    for( const auto& line : m_rows )
    {
        charsUsed += line.size();
    }

    const std::size_t bufferSize{ charsUsed + 1u };
    m_asOne.clear();
    m_asOne.reserve( bufferSize );
    for( const auto& line : m_rows )
    {
        m_asOne.append( line.getSTDString() );
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
    return nullptr;
}

const char* RegularFile::getUtfChar() const
{
    return m_asOne.c_str();
}

// Getters
std::string RegularFile::getLineUtf( std::int32_t inLineNum ) const
{
    if( (std::size_t)inLineNum < m_rows.size() )
    {
        return m_rows[inLineNum].getSTDString();
    }
    return "";
}

std::wstring RegularFile::getLineW( std::int32_t inLineNum ) const
{
    if( (std::size_t)inLineNum < m_rows.size() )
    {
        return m_rows[inLineNum].getSTDWstring();
    }
    return L"";
}

RegularFile::~RegularFile()
{
}
