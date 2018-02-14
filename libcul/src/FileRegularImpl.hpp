#pragma once
#include "CUL/IFile.hpp"
#include "CUL/Path.hpp"
#include <vector>
#include <memory>
namespace CUL
{
    namespace FS
    {
        class FileRegularImpl: public IFile
        {
        public:
            FileRegularImpl();
            FileRegularImpl( const FileRegularImpl& file );
            FileRegularImpl( const std::string& path );
            virtual ~FileRegularImpl();

            Path* getPath() override;

            const bool exists()const override;
            const bool isBinary()const override;

            void reload() override;
            void load() override;
            void unload() override;

            const std::string& firstLine()const override;
            const std::string& lastLine()const override;

        protected:
        private:
            Path path;
            std::vector<std::string> rows;
        };
    }
}