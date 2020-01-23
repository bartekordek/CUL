#include "CUL/Filesystem/Path.hpp"
#include "Filesystem/FSUtils.hpp"

using namespace CUL;
using namespace FS;

String Path::extensionSeparator = String( "." );

CsStr& Path::getDirSeparator()
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

Path::Path( CsStr& path ):
    m_fullPath( path )
{
    preparePaths();
    normalizePaths();
}

Path::Path( const std::string& path ):
    m_fullPath( path )
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

Path& Path::operator=( CsStr& path )
{
    if( m_fullPath != path )
    {
        m_fullPath = path;
        preparePaths();
    }
    return *this;
}

Path& Path::operator=( const char* r )
{
    if( m_fullPath != r )
    {
        m_fullPath = r;
        preparePaths();
    }
    return *this;
}

Path& Path::operator=( const std::string & rhv )
{
    if( m_fullPath != rhv )
    {
        m_fullPath = rhv;
        preparePaths();
    }
    return *this;
}

Path& Path::operator+=( const Path& rhv )
{
    m_fullPath += rhv.m_fullPath;
    preparePaths();
    return *this;
}

Path& Path::operator+=( CsStr& rhv )
{
    m_fullPath = m_fullPath + rhv;
    preparePaths();
    return *this;
}

Path& Path::operator+=( const std::string& rhv )
{
    m_fullPath = m_fullPath + rhv;
    preparePaths();
    return *this;
}

Path Path::operator+( const Path & rhv )
{
    Path result = *this;
    result += rhv;
    return result;
}

Path Path::operator+( CsStr& rhv )
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

CsStr& Path::getPath() const
{
    return m_fullPath;
}

CsStr& Path::getExtension() const
{
    return m_extension;
}

CsStr& Path::getBaseName() const
{
    return m_baseName;
}

CsStr& Path::getDir() const
{
    return m_dir;
}

const bool Path::operator==( const Path& rhv ) const
{
    return m_fullPath == rhv.m_fullPath;
}

Path::operator CsStr() const
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

void Path::normalizePath( String& path )
{
    path.replace( "\\", "/" );
}

const bool Path::exists() const
{
    const bool result = std::experimental::filesystem::is_regular_file( m_fullPath.cStr() );
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