#pragma once

#include "CUL/Filesystem/IFile.hpp"

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

            virtual const bool checkIfFileIsAllRight() const = 0;
            virtual Cunt rowsCount() const = 0;
            virtual Cunt colsCount() const = 0;
            virtual CsStr& getVal( Cunt row, Cunt col ) const = 0;
            virtual void setVal( CsStr& val, Cunt row, Cunt col ) = 0;
            virtual void setDelimeter( CsStr& delimeter ) = 0;
            virtual void fileContainsQuotationMarks( const bool containsQuotationMarks ) = 0;

        protected:
        private:
        };
    }
}
