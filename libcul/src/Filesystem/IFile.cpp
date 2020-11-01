#include "CUL/Filesystem/IFile.hpp"

using namespace CUL;
using namespace FS;

IFile::IFile( const String& fPath ):
    m_path( fPath )
{
}

void IFile::setPath( const String& fPath )
{
    m_path = fPath;
}

bool IFile::exists() const
{
    return getPath().exists();
}

const FileList& IFile::getChildList() const
{
    return m_fileList;
}

void IFile::addChild( IFile* file )
{
    m_fileList.emplace( file );
}

bool IFile::operator==( const IFile* arg ) const
{
    return getPath() == arg->getPath();
}

bool IFile::operator<( const IFile* arg ) const
{
    return getPath() < arg->getPath();
}


IFile::~IFile()
{
    for( const auto& child: m_fileList )
    {
        delete child;
    }
}