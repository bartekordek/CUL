#pragma once

#include "CUL/Path.hpp"
#include "CUL/ICSVFile.hpp"
#include "CUL/STD_vector.hpp"
#include "CUL/STD_string.hpp"

using Row = std::vector<std::string>;
using Rows = std::vector<Row>;

namespace CUL
{
    namespace FS
    {
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
        class CSVFile final:
            public ICSVFile
        {
        public:
            CSVFile( const CSVFile& rhv );
            CSVFile( CstString& fPath );
            ~CSVFile();

            CSVFile& operator=( const CSVFile& rhv );
            CSVFile& operator=( CstString& rPath );
            
            void changePath( const Path& newPath ) override;

            const Path& getPath() const override;

            const bool checkIfFileIsAllRight()const override;
            cunt rowsCount()const override;
            cunt colsCount()const override;
            CstString& getVal( cunt row, cunt col ) const override;
            void setVal( CstString& val, cunt row, cunt col ) override;

            CBool exists()const override;
            CBool isBinary()const override;

            void reload( CBool keepLineEndingCharacter = false ) override;
            void load( CBool keepLineEndingCharacter = false ) override;
            void unload() override;

            CstString& firstLine()const override;
            CstString& lastLine()const override;

            void setDelimeter( CstString& delimeter ) override;

            CstString& getAsOneString()const override;
            const char** getContent()const override;

            cunt getLinesCount()const override;

        protected:
        private:
            CSVFile();
            void parseLine( CstString& line );
            void cacheFile();

            std::string m_delimeter = ",";
            Path m_path;
            Rows m_rows;
            std::string m_cached;
            bool m_keepLineEndingCharacter = false;
        };
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    }
}