#pragma once
#include "CUL.hpp"
#include "Path.hpp"
#include "CUL/STD_memory.hpp"

using cunt = const unsigned int;

namespace CUL
{
    namespace FS
    {
        class CULLib_API IFile
        {
        public:
            IFile( void );
            IFile( CstString& fPath ) = delete;
            IFile( const IFile& file ) = delete;
            virtual ~IFile();

            IFile& operator=( CstString& rPath ) = delete;

            virtual const Path& getPath()const = 0;

            virtual CBool exists()const = 0;
            virtual CBool isBinary()const = 0;

            virtual void changePath( const Path& newPath ) = 0;

            virtual void reload( CBool keepLineEndingCharacter = false ) = 0;
            virtual void load( CBool keepLineEndingCharacter = false ) = 0;
            virtual void unload() = 0;

            virtual CstString& firstLine()const = 0;
            virtual CstString& lastLine()const = 0;

            virtual CstString& getAsOneString()const = 0;
            virtual const char** getContent()const = 0;

            virtual cunt getLinesCount()const = 0;

        protected:
        private:
        };
    }
}