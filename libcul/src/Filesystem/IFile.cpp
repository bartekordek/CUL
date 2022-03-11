#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Filesystem/FSApi.hpp"

#include "CUL/CULInterface.hpp"
#include "CUL/TimeConcrete.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_iterator.hpp"
#include "IMPORT_hash_library.hpp"

using namespace CUL;
using namespace FS;

IFile::IFile( const String& fPath, CUL::CULInterface* interface ) : p_cullInterface( interface ), m_path( fPath )
{
    m_lastModificationTime = p_cullInterface->getFS()->getLastModificationTime( fPath );
}

void IFile::setPath( const String& fPath )
{
    m_path = fPath;
}

void IFile::addLine( const String& )
{
}

void IFile::saveFile()
{
}

void IFile::loadFromString( const String& )
{

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
    if( m_lastModificationTime.getUs() > 0u )
    {
        return m_lastModificationTime;
    }

    if( p_cullInterface->getFS()->fileExist( m_path ) )
    {
        m_lastModificationTime = p_cullInterface->getFS()->getLastModificationTime( m_path );
    }
    return m_lastModificationTime;
}

const String& IFile::getMD5()
{
    if( m_md5.empty() )
    {
        calculateMD5();
    }
    return m_md5;
}

void IFile::calculateMD5()
{
    std::ifstream file( m_path.getString(), std::ios::binary );
    file.unsetf( std::ios::skipws );

    unsigned fileSizeAsNumber = getSizeBytes().toUInt();
    std::vector<unsigned char> vec;
    vec.reserve( fileSizeAsNumber );
    vec.insert( vec.begin(), std::istream_iterator<unsigned char>( file ), std::istream_iterator<unsigned char>() );

    SHA256 sha256;
    m_md5 = sha256( vec.data(), fileSizeAsNumber );

    return;
}

const String& IFile::getSizeBytes()
{
    if( m_sizeBytes.empty() )
    {
        calculateSizeBytes();
    }
    return m_sizeBytes;
}

void IFile::calculateSizeBytes()
{
    /*std::ifstream in( m_path.cStr(), std::ifstream::ate | std::ifstream::binary );
    m_sizeBytes = static_cast<unsigned>(in.tellg());*/
    m_sizeBytes = p_cullInterface->getFS()->getFileSize( m_path );
}

IFile::~IFile()
{
}