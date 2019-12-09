#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/ICSVFile.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
using Row = std::vector<String>;
using Rows = std::vector<Row>;
class CSVFile final:
    public ICSVFile
{
public:
    CSVFile( void );
    CSVFile( const CSVFile& rhv );
    CSVFile( CsStr& fPath );
    ~CSVFile( void );

    CSVFile& operator=( const CSVFile& rhv );
    CSVFile& operator=( CsStr& rPath );

    void changePath( const Path& newPath ) override;

    const Path& getPath() const override;

    const bool checkIfFileIsAllRight()const override;
    cunt rowsCount()const override;
    cunt colsCount()const override;
    CsStr& getVal( cunt row, cunt col ) const override;
    void setVal( CsStr& val, cunt row, cunt col ) override;

    CBool exists()const override;
    CBool isBinary()const override;

    void reload( CBool keepLineEndingCharacter = false ) override;
    void load( CBool keepLineEndingCharacter = false ) override;
    void unload() override;

    CsStr& firstLine()const override;
    CsStr& lastLine()const override;

    void setDelimeter( CsStr& delimeter ) override;

    CsStr& getAsOneString()const override;
    const char** getContent()const override;

    cunt getLinesCount()const override;

    void fileContainsQuotationMarks( const bool containsQuotationMarks ) override;

protected:
private:
    void parseLine( CsStr& line );
    void cacheFile();

    String m_delimeter = ",";
    bool m_cellsContainQuotationMarks = true;
    Path m_path;
    Rows m_rows;
    String m_cached;
    bool m_keepLineEndingCharacter = false;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif
NAMESPACE_END( FS )
NAMESPACE_END( CUL )
