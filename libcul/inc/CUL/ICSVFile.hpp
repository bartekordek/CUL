#pragma once

#include "CUL/IFile.hpp"
using cunt = const unsigned int;
namespace CUL
{
    namespace FS
    {
        class CULLib_API ICSVFile:
            public IFile
        {
        public:
            ICSVFile( void );
            ICSVFile( const ICSVFile& rhv ) = delete;
            virtual ~ICSVFile();

            ICSVFile& operator=( const ICSVFile& rhv ) = delete;

            virtual const bool checkIfFileIsAllRight()const = 0;
            virtual cunt rowsCount()const = 0;
            virtual cunt colsCount()const = 0;
            virtual const std::string& getVal( cunt row, cunt col )const = 0;
            virtual void setVal( const std::string& val, cunt row, cunt col ) = 0;
            virtual void setDelimeter( const std::string& delimeter ) = 0;

        protected:
        private:
        };
    }
}