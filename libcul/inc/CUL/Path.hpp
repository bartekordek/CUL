#pragma once
#include "CUL/CUL.hpp"
#include "MyString.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4251)
#endif
namespace CUL
{
    using CBool = const bool;
    namespace FS
    {
        class CULLib_API Path
        {
        public:
            Path();
            Path( const Path& path );
            Path( CnstMyStr& path );
            Path( const char* r );
            virtual ~Path();

            Path& operator=( CnstMyStr& r );
            Path& operator=( const char* r );
            Path& operator+=( const Path& rhv );
            Path& operator+=( CnstMyStr& rhv );

            CnstMyStr& getPath()const;
            CnstMyStr& getExtension()const;
            CnstMyStr& getBaseName()const;
            CnstMyStr& getDir()const;

            const bool exists()const;

            static CnstMyStr& getDirSeparator();
        protected:
        private:
            void preparePaths();
            MyString fullPath;
            MyString extension;
            MyString baseName;
            MyString dir;

            static MyString directorySeparator;
            static MyString extensionSeparator;
        };
    }
}
#if _MSC_VER
#pragma warning( pop )
#endif