#include "CUL/Filesystem/TextFile.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

using namespace CUL;
using namespace FS;


TextFile::TextFile( const StringWr& fPath, CULInterface* inInterface ) : IFile( fPath, inInterface )
{

}

void TextFile::reload( bool  )
{
}

void TextFile::reload()
{
}

void TextFile::unload()
{
}

const StringWr& TextFile::firstLine() const
{
    return m_values;
}

const StringWr& TextFile::lastLine() const
{
    return m_values;
}

const StringWr& TextFile::getAsOneString() const
{
    return m_values;
}

const char** TextFile::getContent() const
{
    return nullptr;
}

unsigned TextFile::getLinesCount() const
{
    return 0u;
}


void TextFile::changePath( const Path&  )
{
}

const Path& TextFile::getPath() const
{
    return m_path;
}

FileType TextFile::getType() const
{
    return FileType::TXT;
}

TextFile::~TextFile()
{

}
