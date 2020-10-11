#include "CUL/Filesystem/Directory.hpp"

using namespace CUL;
using namespace FS;

Directory::Directory( const String& path ):
    IFile( path )
{
}

const Path& Directory::getPath() const
{
    return m_path;
}

void Directory::changePath( const Path& newPath )
{
    m_path = newPath;
    IFile::setPath( newPath );
}

//TODO
void Directory::reload( Cbool )
{
}

//TODO
void Directory::load( Cbool )
{
}

//TODO
void Directory::unload()
{
}

const String& Directory::firstLine() const
{
    return m_value;
}

const String& Directory::lastLine() const
{
    return m_value;
}

const String& Directory::getAsOneString() const
{
    return m_value;
}

const char ** Directory::getContent() const
{
    return nullptr;
}

//TODO
unsigned Directory::getLinesCount() const
{
    return 0;
}

FileType Directory::getType() const
{
    return FileType::DIRECTORY;
}

Directory::~Directory()
{
}