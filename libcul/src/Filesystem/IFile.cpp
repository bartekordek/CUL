#include "CUL/Filesystem/IFile.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/TimeConcrete.hpp"

using namespace CUL;
using namespace FS;

IFile::IFile( const String& fPath, CUL::CULInterface* interface ):
    p_cullInterface( interface ),
    m_path( fPath )
{
    m_lastModificationTime = p_cullInterface->getFS()->getLastModificationTime( fPath );
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

bool IFile::operator==( const IFile& arg ) const
{
    return getPath() == arg.getPath();
}

bool IFile::operator<( const IFile& arg ) const
{
    return getPath() < arg.getPath();
}

bool IFile::operator>( const IFile& arg ) const
{
    return getPath() > arg.getPath();
}

TimeConcrete IFile::getCreationTime()
{
    return m_creationTime;
}

TimeConcrete IFile::getLastModificationTime()
{
    if( p_cullInterface->getFS()->fileExist( m_path ) )
    {
        m_lastModificationTime = p_cullInterface->getFS()->getLastModificationTime( m_path );
    }
    return m_lastModificationTime;
}

IFile::~IFile()
{
}