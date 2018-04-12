#pragma once

#include "CUL/Path.hpp"
#include "CUL/ICSVFile.hpp"
#include <vector>
#include <string>


using Row = std::vector<std::string>;
using Rows = std::vector<Row>;

namespace CUL
{
    namespace FS
    {
        class CSVFile final:
            public ICSVFile
        {
        public:
            CSVFile( const std::string& fPath );
            ~CSVFile();

            IFile& operator=( const std::string& rPath );
            void changePath( const Path& newPath ) override;

            const Path& getPath() const override;

            const bool checkIfFileIsAllRight()const override;
            cunt rowsCount()const override;
            cunt colsCount()const override;
            const std::string& getVal( cunt row, cunt col )const override;
            void setVal( const std::string& val, cunt row, cunt col ) override;

            const bool exists()const override;
            const bool isBinary()const override;

            void reload( const bool keepLineEndingCharacter = false ) override;
            void load( const bool keepLineEndingCharacter = false ) override;
            void unload() override;

            const std::string& firstLine()const override;
            const std::string& lastLine()const override;

            void setDelimeter( const std::string& delimeter ) override;

            const std::string& getAsOneString()const override;
            const char** getContent()const override;

            cunt getLinesCount()const override;

        protected:
        private:
            CSVFile();
            void parseLine( const std::string& line );

            void cacheFile();

            std::string m_delimeter = ",";
            Path m_path;
            Rows m_rows;
            std::string m_cached;
            bool m_keepLineEndingCharacter = false;
        };
    }
}