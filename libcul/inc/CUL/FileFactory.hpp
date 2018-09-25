#pragma once
#include "IFile.hpp"
#include "CUL/ICSVFile.hpp"
#include "CUL/JSON/IJSONFile.hpp"
namespace CUL
{
    namespace FS
    {
        using IFilePtr = std::shared_ptr<IFile>;
        using ICSVFilePtr = std::shared_ptr<ICSVFile>;
        using IJSONFilePtr = std::shared_ptr<JSON::IJSONFile>;
        class CULLib_API FileFactory
        {
        public:
            static IFile* createRegularFile();
            static ICSVFile* createCSVFile();
            static JSON::IJSONFile* createJSONFile();

            static IFile* createRegularFile( const Path& path );
            static ICSVFile* createCSVFile( const Path& path );
            static JSON::IJSONFile* createJSONFile( const Path& path );
        protected:
        private:
        };
    }
}