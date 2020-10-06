#include "CUL/Filesystem/Directory.hpp"

using namespace CUL;
using namespace FS;

Directory::Directory( CsStr& path ):
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

CsStr& Directory::firstLine() const
{
    return m_value;
}

CsStr& Directory::lastLine() const
{
    return m_value;
}

CsStr& Directory::getAsOneString() const
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