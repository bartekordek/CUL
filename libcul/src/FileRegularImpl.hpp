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

            IFile& operator=( const std::string& rPath );
            void changePath( const Path& newPath ) override;

            const Path& getPath() const override;

            const bool exists()const override;
            const bool isBinary()const override;

            void reload( const bool keepLineEndingCharacter = false ) override;
            void load( const bool keepLineEndingCharacter = false ) override;
            void unload() override;

            const std::string& firstLine()const override;
            const std::string& lastLine()const override;

            const std::string& getAsOneString()const override;
            const char** getContent()const override;

            cunt getLinesCount()const override;

        protected:
        private:
            void cacheFile();

            Path path;
            std::vector<std::string> rows;
            std::vector<char*> m_rowsAsChars;
            std::string m_cached;
            bool m_keepLineEndingCharacter = false;
        };
    }
}