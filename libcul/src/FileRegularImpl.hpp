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
            FileRegularImpl( const Path& path );
            virtual ~FileRegularImpl();

            IFile& operator=( const Path& rPath );
            void changePath( const Path& newPath ) override;

            const Path& getPath() const override;

            CBool exists()const override;
            CBool isBinary()const override;

            void reload( CBool keepLineEndingCharacter = false ) override;
            void load( CBool keepLineEndingCharacter = false ) override;
            void unload() override;

            CnstMyStr& firstLine()const override;
            CnstMyStr& lastLine()const override;

            CnstMyStr& getAsOneString()const override;
            const char** getContent()const override;

            cunt getLinesCount()const override;

        protected:
        private:
            void cacheFile();

            Path m_path;
            std::vector<MyString> rows;
            std::vector<char*> m_rowsAsChars;
            MyString m_cached;
            bool m_keepLineEndingCharacter = false;
        };
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    }
}