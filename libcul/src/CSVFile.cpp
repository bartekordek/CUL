#include "CSVFile.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

using namespace CUL;
using namespace FS;

CSVFile::CSVFile( const String& fPath, CULInterface* interface ):
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

unsigned CSVFile::rowsCount() const
{
    return static_cast<unsigned>( m_rows.size() );
}

unsigned CSVFile::colsCount() const
{
    //TODO: what if there are no rows?
    return static_cast<unsigned>( m_rows[0].size() );
}

const String& CSVFile::getVal( Cunt row, Cunt col ) const
{
    return m_rows[row][col];
}

void CSVFile::setVal( const String& val, Cunt row, Cunt col )
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

void CSVFile::reload( Cbool keepLineEndingCharacter )
{
    unload();
    load( keepLineEndingCharacter );
}

void CSVFile::load( Cbool keepLineEndingCharacter )
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
    auto delimeterPos = line.string().find( m_delimeter.string() );
    std::string cell;
    while( delimeterPos != std::string::npos )
    {
        size_t cellEnd = m_cellsContainQuotationMarks ?
            delimeterPos - 2 : delimeterPos;

        size_t cellStart = m_cellsContainQuotationMarks ?
            static_cast<size_t>( 1 ) : static_cast<size_t>( 0 );

        size_t newCellOffset = m_cellsContainQuotationMarks ?
            static_cast<size_t>( 3 ) : static_cast<size_t>( 0 );

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