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
#ifdef _MSC_VER
            __pragma( warning( push ) ) \
            __pragma( warning( disable:4100 ) )
#endif
            ICSVFile( const std::string& fPath )
            {
            }
#ifdef _MSC_VER
            __pragma( warning( pop ) )
#endif
            virtual ~ICSVFile() = default;

            virtual const bool checkIfFileIsAllRight()const = 0;
            virtual cunt rowsCount()const = 0;
            virtual cunt colsCount()const = 0;
            virtual const std::string& getVal( cunt row, cunt col )const = 0;
            virtual void setVal( const std::string& val, cunt row, cunt col ) = 0;
            virtual void setDelimeter( const std::string& delimeter ) = 0;

        protected:
        private:
            ICSVFile();
        };
    }
}