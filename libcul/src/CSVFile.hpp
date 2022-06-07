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
    CSVFile( const String& fPath, CULInterface* interface );

    void changePath( const Path& newPath ) override;

    const Path& getPath() const override;

    bool checkIfFileIsAllRight() const override;
    const String& getVal( unsigned row, unsigned col ) const override;
    void setVal( const String& val, unsigned row, unsigned col ) override;

    FileType getType() const override;

    void reload( bool keepLineEndingCharacter ) override;
    void reload() override;
    void load( bool keepLineEndingCharacter = false ) override;
    void unload() override;

    const String& firstLine() const override;
    const String& lastLine() const override;

    void setDelimeter( const String& delimeter ) override;

    const String& getAsOneString() const override;
    const char** getContent() const override;

    unsigned getLinesCount() const override;

    void fileContainsQuotationMarks( const bool containsQuotationMarks ) override;

    ~CSVFile();
protected:
private:
    unsigned getRowsCount() const override;
    unsigned getColsCount() const override;
    void loadCSV( bool valuesContainQuotationMarks, bool keepLineEndingCharacter = false ) override;
    void parseLine( const String& line );
    void cacheFile();

    String m_delimeter = ",";
    bool m_cellsContainQuotationMarks = true;
    Path m_path;
    Rows m_rows;
    unsigned m_columnsCount = 0;
    String m_cached;
    bool m_keepLineEndingCharacter = false;


// Deleted:
    CSVFile() = delete;
    CSVFile( const CSVFile& rhv ) = delete;
    CSVFile( CSVFile&& rhv ) = delete;
    CSVFile& operator=( const CSVFile& rhv ) = delete;
    CSVFile& operator=( CSVFile&& rhv ) = delete;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif
NAMESPACE_END( FS )
NAMESPACE_END( CUL )