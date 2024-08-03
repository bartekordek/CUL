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
    infile.open( m_path.getPath().getChar(),
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
    std::vector<String> splitLine = line.split( m_delimeter );

    if( m_cellsContainQuotationMarks == false )
    {
        for( String& cell : splitLine )
        {
            const Length cellLength = cell.size();
            if( cell[0] == '\"' && cell[cellLength - 1] == '\"' )
            {
                cell.erase( cellLength - 1 );
                cell.erase( 0 );
            }
        }
    }

    m_columnsCount = std::max( m_columnsCount, (unsigned)splitLine.size() );

    m_rows.push_back( splitLine );
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
            line.append( cell );
            line.append( m_delimeter );
        }

        m_cached.append( line );
        m_cached.append('\n');
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