#pragma once
#include "IFile.hpp"
namespace CUL
{
    namespace FS
    {
        using IFilePtr = std::shared_ptr<IFile>;
        class CULLib_API FileFactory
        {
        public:
            static IFilePtr createRegularFile( const Path& path );
            static IFilePtr createCSVFile( const Path& path );
        protected:
        private:
        };
    }
}