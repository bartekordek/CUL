#include "CSVFile.hpp"
#include "STD_fstream.hpp"

using namespace CUL;
using namespace FS;

CSVFile::CSVFile( void )
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

CSVFile::CSVFile( CnstMyStr& fPath ):
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

CSVFile& CSVFile::operator=( CnstMyStr& rPath )
{
    changePath( rPath );
    return *this;
}

void CSVFile::changePath( const Path& newPath )
{
    this->m_path = newPath;
    reload();
}

const bool CSVFile::checkIfFileIsAllRight()const
{
    return true;//TODO
}

cunt CSVFile::rowsCount()const
{
    return static_cast<cunt>( this->m_rows.size() );
}

cunt CSVFile::colsCount()const
{
    return static_cast<cunt>( this->m_rows[0].size() );
}

CnstMyStr& CSVFile::getVal( cunt row, cunt col )const
{
    return this->m_rows[ row ][ col ];
}

void CSVFile::setVal( CnstMyStr& val, cunt row, cunt col )
{
    this->m_rows[ row ][ col ] = val;
}

const bool CSVFile::exists()const
{
    return this->m_path.exists();
}

const bool CSVFile::isBinary()const
{
    return false;//TODO
}

void CSVFile::setDelimeter( CnstMyStr& delimeter )
{
    this->m_delimeter = delimeter;
}

void CSVFile::reload( CBool keepLineEndingCharacter )
{
    unload();
    load( keepLineEndingCharacter );
}

void CSVFile::load( CBool keepLineEndingCharacter )
{
    this->m_keepLineEndingCharacter = keepLineEndingCharacter;
    std::ifstream infile;
    infile.open(
        this->m_path.getPath().cStr(),
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

void CSVFile::parseLine( CnstMyStr& line )
{
    Row inRow;//TODO: there is a problem with parsing.
    auto lineCp = line;//huj
    auto delimeterPos = line.string().find( this->m_delimeter.string() );
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
        delimeterPos = lineCp.string().find( this->m_delimeter.string() );
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

    this->m_rows.push_back( inRow );
}

void CSVFile::unload()
{
    this->m_rows.clear();
}

CnstMyStr& CSVFile::firstLine()const
{
    return this->m_rows.front()[0];
}

CnstMyStr& CSVFile::lastLine()const
{
    return this->m_rows.back()[ this->m_rows.size() - 1 ];
}

const Path& CSVFile::getPath()const
{
    return this->m_path;
}

CnstMyStr& CSVFile::getAsOneString()const
{
    return this->m_cached;
}

void CSVFile::cacheFile()
{
    this->m_cached = "";
    for( const auto& row : this->m_rows )
    {
        MyString line;
        for( const auto& cell: row )
        {
            line += cell;
            line += this->m_delimeter;
        }

        this->m_cached += line;
        this->m_cached += "\n";
    }
}

cunt CSVFile::getLinesCount()const
{
    return static_cast< cunt >( this->m_rows.size() );
}

void CSVFile::fileContainsQuotationMarks( const bool containsQuotationMarks )
{
    this->m_cellsContainQuotationMarks = containsQuotationMarks;
}

const char** CSVFile::getContent()const
{
    return nullptr;//TODO
}
