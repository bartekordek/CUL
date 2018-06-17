#pragma once

#include "CUL/IFile.hpp"
#include "CUL/Path.hpp"
#include "CUL/STD_vector.hpp"
#include "CUL/STD_memory.hpp"

namespace CUL
{
    namespace FS
    {
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif
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

            CBool exists()const override;
            CBool isBinary()const override;

            void reload( CBool keepLineEndingCharacter = false ) override;
            void load( CBool keepLineEndingCharacter = false ) override;
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
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    }
}