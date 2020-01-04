#include "CSVFile.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

using namespace CUL;
using namespace FS;

CSVFile::CSVFile()
{
}
CSVFile::CSVFile( const CSVFile & rhv ):
    m_delimeter( rhv.m_delimeter ),
    m_path( rhv.m_path ),
    m_rows( rhv.m_rows ),
    m_cached( rhv.m_cached ),
    m_keepLineEndingCharacter( rhv.m_keepLineEndingCharacter )
{

}

CSVFile::CSVFile( CsStr& fPath ):
    m_path( fPath )
{

}

CSVFile::~CSVFile()
{

}

CSVFile& CSVFile::operator=( const CSVFile& rhv )
{
    if( &rhv != this )
    {
        m_delimeter = rhv.m_delimeter;
        m_path = rhv.m_path;
        m_rows = rhv.m_rows;
        m_cached = rhv.m_cached;
        m_keepLineEndingCharacter = rhv.m_keepLineEndingCharacter;
    }
    return *this;
}

CSVFile& CSVFile::operator=( CsStr& rPath )
{
    changePath( rPath );
    return *this;
}

void CSVFile::changePath( const Path& newPath )
{
    m_path = newPath;
    reload();
}

const bool CSVFile::checkIfFileIsAllRight() const
{
    return true;//TODO
}

Cunt CSVFile::rowsCount() const
{
    return static_cast<Cunt>( m_rows.size() );
}

Cunt CSVFile::colsCount() const
{
    return static_cast<Cunt>( m_rows[0].size() );
}

CsStr& CSVFile::getVal( Cunt row, Cunt col ) const
{
    return m_rows[ row ][ col ];
}

void CSVFile::setVal( CsStr& val, Cunt row, Cunt col )
{
    m_rows[ row ][ col ] = val;
}

const bool CSVFile::exists() const
{
    return m_path.exists();
}

const bool CSVFile::isBinary() const
{
    return false;//TODO
}

void CSVFile::setDelimeter( CsStr& delimeter )
{
    m_delimeter = delimeter;
}

void CSVFile::reload( CBool keepLineEndingCharacter )
{
    unload();
    load( keepLineEndingCharacter );
}

void CSVFile::load( CBool keepLineEndingCharacter )
{
    m_keepLineEndingCharacter = keepLineEndingCharacter;
    std::ifstream infile;
    infile.open(
        m_path.getPath().cStr(),
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
        parseLine( line );
    }
    infile.close();

    cacheFile();
}

void CSVFile::parseLine( CsStr& line )
{
    Row inRow;//TODO: there is a problem with parsing.
    auto lineCp = line;//huj
    auto delimeterPos = line.string().find( m_delimeter.string() );
    std::string cell;
    while( delimeterPos != std::string::npos )
    {
        size_t cellEnd = m_cellsContainQuotationMarks ?
            delimeterPos - 2 : delimeterPos;

        size_t cellStart = m_cellsContainQuotationMarks ?
            static_cast<size_t>( 1 ) : static_cast<size_t>(0);

        size_t newCellOffset = m_cellsContainQuotationMarks ?
            static_cast<size_t>(3) : static_cast<size_t>(0);

        cell = lineCp.string().substr( cellStart, cellEnd );
        inRow.push_back( cell );
        lineCp = lineCp.string().substr( cellEnd + newCellOffset );
        delimeterPos = lineCp.string().find( m_delimeter.string() );
    }

    if( m_cellsContainQuotationMarks )
    {
        cell = lineCp.string().substr( 1, lineCp.string().size() - 2 );
    }
    else
    {
        cell = lineCp.string().substr( 0, lineCp.string().size() );
    }
    inRow.push_back( cell );

    m_rows.push_back( inRow );
}

void CSVFile::unload()
{
    m_rows.clear();
}

CsStr& CSVFile::firstLine() const
{
    return m_rows.front()[0];
}

CsStr& CSVFile::lastLine() const
{
    return m_rows.back()[ m_rows.size() - 1 ];
}

const Path& CSVFile::getPath() const
{
    return m_path;
}

CsStr& CSVFile::getAsOneString() const
{
    return m_cached;
}

void CSVFile::cacheFile()
{
    m_cached = "";
    for( const auto& row : m_rows )
    {
        String line;
        for( const auto& cell: row )
        {
            line += cell;
            line += m_delimeter;
        }

        m_cached += line;
        m_cached += "\n";
    }
}

Cunt CSVFile::getLinesCount() const
{
    return static_cast< Cunt >( m_rows.size() );
}

void CSVFile::fileContainsQuotationMarks( const bool containsQuotationMarks )
{
    m_cellsContainQuotationMarks = containsQuotationMarks;
}

const char** CSVFile::getContent() const
{
    return nullptr;//TODO
}
