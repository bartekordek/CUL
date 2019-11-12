#include "CUL/Filesystem/Path.hpp"
#include "Filesystem/FSUtils.hpp"

using namespace CUL;
using namespace FS;

MyString Path::extensionSeparator = MyString( "." );

CnstMyStr& Path::getDirSeparator()
{
    return extensionSeparator;
}

Path::Path()
{

}

Path::Path( const Path& path ): 
    m_fullPath( path.m_fullPath ),
    m_extension( path.m_extension ),
    m_baseName( path.m_baseName ),
    m_dir( path.m_dir )
{
    normalizePaths();
}

Path::Path( CnstMyStr& path ):
    m_fullPath(path)
{
    preparePaths();
    normalizePaths();
}

Path::Path( const char* r ):
    m_fullPath( r )
{
    preparePaths();
}

Path::~Path()
{

}

Path& Path::operator=( CnstMyStr& path )
{
    if( this->m_fullPath != path )
    {
        this->m_fullPath = path;
        preparePaths();
    }
    return *this;
}

Path& Path::operator=( const char* r )
{
    if ( this->m_fullPath != r )
    {
        this->m_fullPath = r;
        preparePaths();
    }
    return *this;
}

Path& Path::operator+=( const Path& rhv )
{
    this->m_fullPath += rhv.m_fullPath;
    preparePaths();
    return *this;
}

Path& Path::operator+=( CnstMyStr& rhv )
{
    this->m_fullPath = this->m_fullPath + rhv;
    preparePaths();
    return *this;
}

Path Path::operator+( const Path & rhv )
{
    Path result = *this;
    result += rhv;
    return result;
}

Path Path::operator+( CnstMyStr& rhv )
{
	Path result = *this;
	result += rhv;
	return result;
}

Path Path::operator+( const char* rhv )
{
	Path result = *this;
	result += std::string( rhv );
	return result;
}

CnstMyStr& Path::getPath()const
{
    return this->m_fullPath;
}

CnstMyStr& Path::getExtension()const
{
    return this->m_extension;
}

CnstMyStr& Path::getBaseName()const
{
    return this->m_baseName;
}

CnstMyStr& Path::getDir()const
{
    return this->m_dir;
}

const bool Path::operator==( const Path& rhv ) const
{
    return this->m_fullPath == rhv.m_fullPath;
}

Path::operator CnstMyStr() const
{
    return m_fullPath;
}

void Path::preparePaths()
{
    FsPath bPath( m_fullPath.cStr() );
#if defined CUL_WINDOWS
    m_baseName = ws2s( bPath.stem().c_str() );
    m_extension = ws2s( bPath.extension().c_str() );
    m_dir = ws2s( bPath.parent_path().c_str() );
#else
    m_baseName = bPath.stem().c_str();
    m_extension = bPath.extension().c_str();
    m_dir = bPath.parent_path().c_str();
#endif
    normalizePaths();
}

void Path::normalizePaths()
{
    normalizePath( m_fullPath );
    normalizePath( m_dir );
}

void Path::normalizePath( MyString& path )
{
    path.replace( "\\", "/" );
}

const bool Path::exists() const
{
    const bool result = std::experimental::filesystem::is_regular_file( this->m_fullPath.cStr() );
    return result;
}

const bool CULLib_API CUL::FS::operator<( const Path & lhv, const Path & rhv )
{
    return lhv.getPath() < rhv.getPath();
}

const Path CULLib_API CUL::FS::operator+( const Path& lval, const Path& rval )
{
    Path result( lval );
    result += rval;
    return result;
}