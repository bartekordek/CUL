#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/Path.hpp"
#include "CUL/ICSVFile.hpp"
#include "CUL/STD_vector.hpp"
#include "CUL/MyString.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

using Row = std::vector<MyString>;
using Rows = std::vector<Row>;

class CSVFile final:
    public ICSVFile
{
public:
    CSVFile( void );
    CSVFile( const CSVFile& rhv );
    CSVFile( CnstMyStr& fPath );
    ~CSVFile( void );

    CSVFile& operator=( const CSVFile& rhv );
    CSVFile& operator=( CnstMyStr& rPath );

    void changePath( const Path& newPath ) override;

    const Path& getPath() const override;

    const bool checkIfFileIsAllRight()const override;
    cunt rowsCount()const override;
    cunt colsCount()const override;
    CnstMyStr& getVal( cunt row, cunt col ) const override;
    void setVal( CnstMyStr& val, cunt row, cunt col ) override;

    CBool exists()const override;
    CBool isBinary()const override;

    void reload( CBool keepLineEndingCharacter = false ) override;
    void load( CBool keepLineEndingCharacter = false ) override;
    void unload() override;

    CnstMyStr& firstLine()const override;
    CnstMyStr& lastLine()const override;

    void setDelimeter( CnstMyStr& delimeter ) override;

    CnstMyStr& getAsOneString()const override;
    const char** getContent()const override;

    cunt getLinesCount()const override;

    void fileContainsQuotationMarks( const bool containsQuotationMarks ) override;

protected:
private:
    void parseLine( CnstMyStr& line );
    void cacheFile();

    MyString m_delimeter = ",";
    bool m_cellsContainQuotationMarks = true;
    Path m_path;
    Rows m_rows;
    MyString m_cached;
    bool m_keepLineEndingCharacter = false;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif
NAMESPACE_END( FS )
NAMESPACE_END( CUL )