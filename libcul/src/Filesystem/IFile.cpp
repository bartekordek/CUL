#include "CUL/Filesystem/IFile.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;
using namespace FS;

IFile::IFile()
{
    std::cout << "IFile::IFile() " << this << "\n";
}

Cbool IFile::exists() const
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

const bool IFile::operator==( const IFile* arg ) const
{
    return getPath() == arg->getPath();
}

const bool IFile::operator<( const IFile* arg ) const
{
    return getPath() < arg->getPath();
}


IFile::~IFile()
{
    std::cout << "IFile::~IFile() " << this << "\n";
    for( const auto& child: m_fileList )
    {
        delete child;
    }
}