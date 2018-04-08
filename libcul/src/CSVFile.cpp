#include "CSVFile.hpp"
#include <fstream>

using namespace CUL;
using namespace FS;

CSVFile::CSVFile( const std::string& fPath ):
    ICSVFile( fPath ),
    m_path( fPath )
{

}

CSVFile::~CSVFile()
{

}

IFile& CSVFile::operator=( const std::string& rPath )
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

const std::string& CSVFile::getVal( cunt row, cunt col )const
{
    return this->m_rows[ row ][ col ];
}

void CSVFile::setVal( const std::string& val, cunt row, cunt col )
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

void CSVFile::setDelimeter( const std::string& delimeter )
{
    this->m_delimeter = delimeter;
}

void CSVFile::load()
{
    std::ifstream infile;
    infile.open(
        this->m_path.getPath(),
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

void CSVFile::parseLine( const std::string& line )
{
    Row inRow;
    auto lineCp = line;
    auto delimeterPos = line.find( this->m_delimeter );
    while( delimeterPos != std::string::npos )
    {
        auto cell = lineCp.substr( 1, delimeterPos - 1 );
        inRow.push_back( cell );
        lineCp = lineCp.substr( delimeterPos + 2 );
        delimeterPos = lineCp.find( this->m_delimeter );
    }
    this->m_rows.push_back( inRow );
}

void CSVFile::unload()
{
}

void CSVFile::reload()
{
}

const std::string& CSVFile::firstLine()const
{
    return this->m_rows.front()[0];
}

const std::string& CSVFile::lastLine()const
{
    return this->m_rows.back()[ this->m_rows.size() - 1 ];
}

const Path& CSVFile::getPath()const
{
    return this->m_path;
}

const std::string& CSVFile::getAsOneString()const
{
    return this->m_cached;
}

void CSVFile::cacheFile()
{
    this->m_cached = "";
    for( const auto& row : this->m_rows )
    {
        std::string line;
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

const char** CSVFile::getContent()const
{
    return nullptr;//TODO
}