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
    ~CSVFile();

    void changePath( const Path& newPath ) override;

    const Path& getPath() const override;

    bool checkIfFileIsAllRight() const override;
    unsigned rowsCount() const override;
    unsigned colsCount() const override;
    const String& getVal( Cunt row, Cunt col ) const override;
    void setVal( const String& val, Cunt row, Cunt col ) override;

    FileType getType() const override;

    void reload( Cbool keepLineEndingCharacter = false ) override;
    void load( Cbool keepLineEndingCharacter = false ) override;
    void unload() override;

    const String& firstLine() const override;
    const String& lastLine() const override;

    void setDelimeter( const String& delimeter ) override;

    const String& getAsOneString() const override;
    const char** getContent() const override;

    unsigned getLinesCount() const override;

    void fileContainsQuotationMarks( const bool containsQuotationMarks ) override;

protected:
private:
    void parseLine( const String& line );
    void cacheFile();

    String m_delimeter = ",";
    bool m_cellsContainQuotationMarks = true;
    Path m_path;
    Rows m_rows;
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