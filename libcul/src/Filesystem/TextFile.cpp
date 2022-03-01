#include "CUL/Filesystem/TextFile.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

using namespace CUL;
using namespace FS;


TextFile::TextFile( const String& fPath, CULInterface* interface ) : IFile( fPath, interface )
{

}

void TextFile::reload( bool  )
{
}

void TextFile::load( bool  )
{
}

void TextFile::unload()
{
}

const String& TextFile::firstLine() const
{
    return m_values;
}

const String& TextFile::lastLine() const
{
    return m_values;
}

const String& TextFile::getAsOneString() const
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

TextFile::~TextFile()
{

}