#pragma once
#include <CUL/CUL.hpp>
#include "CUL/STD_string.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4251)
#endif
namespace CUL
{
    namespace FS
    {
        using CBool = const bool;
        using CstString = const std::string;
        class CULLib_API Path
        {
        public:
            Path();
            Path( const Path& path );
            Path( CstString& path );
            Path( const char* r );
            virtual ~Path();

            Path& operator=( const std::string& r );
            Path& operator=( const char* r );

            CstString& getPath()const;
            CstString& getExtension()const;
            CstString& getBaseName()const;
            CstString& getDir()const;

            const bool exists()const;

            static CstString& getDirSeparator();
        protected:
        private:
            void preparePaths();
            std::string fullPath;
            std::string extension;
            std::string baseName;
            std::string dir;

            static std::string directorySeparator;
            static std::string extensionSeparator;
        };

        Path CULLib_API operator+( const Path& l, const std::string& r );
        Path CULLib_API operator+( const Path& l, const Path& r );
    }
}
#if _MSC_VER
#pragma warning( pop )
#endif