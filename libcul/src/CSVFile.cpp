#include "CSVFile.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

using namespace CUL;
using namespace FS;

CSVFile::CSVFile( const String& fPath, CULInterface* interface ) :
    ICSVFile( fPath, interface ),
    m_path( fPath )
{
}

void CSVFile::changePath( const Path& newPath )
{
    m_path = newPath;
    reload();
}

bool CSVFile::checkIfFileIsAllRight() const
{
    return true;//TODO
}

unsigned CSVFile::getRowsCount() const
{
    return static_cast<unsigned>( m_rows.size() );
}

unsigned CSVFile::getColsCount() const
{
    //TODO: what if there are no rows?
    return m_columnsCount;
}

const String& CSVFile::getVal( unsigned row, unsigned col ) const
{
    return m_rows[row][col];
}

void CSVFile::setVal( const String& val, unsigned row, unsigned col )
{
    m_rows[row][col] = val;
}

FileType CSVFile::getType() const
{
    return FileType::TXT;
}

void CSVFile::setDelimeter( const String& delimeter )
{
    m_delimeter = delimeter;
}

void CSVFile::reload( bool keepLineEndingCharacter )
{
    unload();
    load( keepLineEndingCharacter );
}

void CSVFile::reload()
{
    unload();
    load( m_keepLineEndingCharacter );
}

void CSVFile::loadCSV( bool valuesContainQuotationMarks, bool keepLineEndingCharacter )
{
    m_cellsContainQuotationMarks = valuesContainQuotationMarks;
    load( keepLineEndingCharacter );
}

void CSVFile::load( bool keepLineEndingCharacter )
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

void CSVFile::parseLine( const String& line )
{
    Row inRow;//TODO: there is a problem with parsing.
    auto lineCp = line;//huj
    std::int32_t delimeterPos = line.find( m_delimeter );
    String cell;
    while( delimeterPos != -1 )
    {
        std::int32_t cellEnd = m_cellsContainQuotationMarks ? delimeterPos - 2 : delimeterPos;
        std::int32_t cellStart = m_cellsContainQuotationMarks ? 1 : 0;
        std::int32_t newCellOffset = m_cellsContainQuotationMarks ? 3 : 1;

        cell = lineCp.substr( cellStart, cellEnd );
        inRow.push_back( cell );
        lineCp = lineCp.substr( cellEnd + newCellOffset );
        delimeterPos = lineCp.find( m_delimeter );
    }

    if( m_cellsContainQuotationMarks )
    {
        cell = lineCp.substr( 1, lineCp.size() - 2 );
    }
    else
    {
        cell = lineCp.substr( 0, lineCp.size() );
    }

    if( !cell.empty() )
    {
        inRow.push_back( cell );
    }

    m_columnsCount = std::max( m_columnsCount, (unsigned)inRow.size() );

    if( !inRow.empty() )
    {
        m_rows.push_back( inRow );
    }
}

void CSVFile::unload()
{
    m_rows.clear();
}

const String& CSVFile::firstLine() const
{
    return m_rows.front()[0];
}

const String& CSVFile::lastLine() const
{
    return m_rows.back()[m_rows.size() - 1];
}

const Path& CSVFile::getPath() const
{
    return m_path;
}

const String& CSVFile::getAsOneString() const
{
    return m_cached;
}

void CSVFile::cacheFile()
{
    m_cached = "";
    for( const auto& row : m_rows )
    {
        String line;
        for( const auto& cell : row )
        {
            line += cell;
            line += m_delimeter;
        }

        m_cached += line;
        m_cached += "\n";
    }
}

unsigned CSVFile::getLinesCount() const
{
    return static_cast<unsigned>( m_rows.size() );
}

void CSVFile::fileContainsQuotationMarks( const bool containsQuotationMarks )
{
    m_cellsContainQuotationMarks = containsQuotationMarks;
}

const char** CSVFile::getContent() const
{
    return nullptr;//TODO
}


CSVFile::~CSVFile()
{
}