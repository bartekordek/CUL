#include "CUL/Filesystem/Path.hpp"
#include "Filesystem/FSUtils.hpp"

using namespace CUL;
using namespace FS;

String Path::extensionSeparator = String( "." );

const String& Path::getDirSeparator()
{
    return extensionSeparator;
}

Path::Path()
{
}

Path::Path( const Path& path ):
    m_isDir( path.m_isDir ),
    m_fullPath( path.m_fullPath ),
    m_extension( path.m_extension ),
    m_baseName( path.m_baseName ),
    m_dir( path.m_dir )
{
    normalizePaths();
}

Path::Path( Path&& path ): m_isDir( path.m_isDir ),
    m_fullPath( std::move( path.m_fullPath ) ),
    m_extension( std::move( path.m_extension ) ),
    m_baseName( std::move( path.m_baseName ) ),
    m_dir( std::move( path.m_dir ) )
{
    normalizePaths();
}

Path::Path( const String& path ) :
    m_fullPath( path )
{
    preparePaths();
    normalizePaths();
}

Path::Path( const std::string& path ) : m_fullPath( path )
{
    preparePaths();
    normalizePaths();
}

Path::Path( const char* r ): m_fullPath( r )
{
    preparePaths();
}

Path& Path::operator=( const Path& path )
{
    if( this != &path )
    {
        m_fullPath = path.m_fullPath;
        m_extension = path.m_extension;
        m_baseName = path.m_baseName;
        m_dir = path.m_dir;
    }
    return *this;
}

Path& Path::operator=( Path&& path )
{
    if( this != &path )
    {
        m_isDir = path.m_isDir;
        m_fullPath = std::move( path.m_fullPath );
        m_extension = std::move( path.m_extension );
        m_baseName = std::move( path.m_baseName );
        m_dir = std::move( path.m_dir );
    }
    return *this;
}

Path& Path::operator=( const String& path )
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
    String right = r;
    if( m_fullPath != right )
    {
        m_fullPath = right;
        preparePaths();
    }
    return *this;
}

Path& Path::operator=( const std::string& rhv )
{
    String right = rhv;
    if( m_fullPath != right )
    {
        m_fullPath = right;
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

Path& Path::operator+=( const String& rhv )
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

Path Path::operator+( const String& rhv )
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

const String& Path::getPath() const
{
    return m_fullPath;
}

const String& Path::getExtension() const
{
    return m_extension;
}

const String& Path::getBaseName() const
{
    return m_baseName;
}

const String& Path::getDir() const
{
    return m_dir;
}

uint64_t Path::getFileSize() const
{
#ifdef _MSC_VER
    FsPath file( m_fullPath.wstring() );
#else
    FsPath file( m_fullPath.cStr() );
#endif
#if defined( _MSC_VER ) && _MSC_VER < 1920
    return std::experimental::filesystem::file_size( file );
#else
    return std::filesystem::file_size( file );
#endif
}

void Path::setIsDir( bool isDir )
{
    m_isDir = isDir;
}

bool Path::getIsDir() const
{
    return m_isDir;
}

bool Path::operator==( const Path& rhv ) const
{
    return m_fullPath == rhv.m_fullPath;
}

bool Path::operator!=( const Path& rhv ) const
{
    return m_fullPath != rhv.m_fullPath;
}

bool Path::operator<( const Path& rhv ) const
{
    return m_fullPath < rhv.m_fullPath;
}

bool Path::operator>( const Path& rhv ) const
{
    return m_fullPath > rhv.m_fullPath;
}

Path::operator const String() const
{
    return m_fullPath;
}

void Path::preparePaths()
{
    if( m_fullPath.empty() )
    {
        return;
    }

#if defined _MSC_VER
    FsPath bPath( m_fullPath.wstring() );
    m_baseName = bPath.stem();
    m_extension = bPath.extension();
    m_dir = bPath.parent_path();
#else
    FsPath bPath( m_fullPath.string() );
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
#ifdef _MSC_VER
    path.replace( std::wstring( L"\\" ), std::wstring( L"/" ) );
#else
    path.replace( "\\", "/" );
#endif
}

bool Path::exists() const
{
#if defined( _MSC_VER ) && _MSC_VER < 1920
    const bool result = std::experimental::filesystem::is_regular_file( m_fullPath.cStr() );
#else
    const bool result = std::filesystem::is_regular_file(m_fullPath.cStr());
#endif
    return result;
}

const Path CULLib_API CUL::FS::operator+( const Path& lval, const Path& rval )
{
    Path result( lval );
    result += rval;
    return result;
}

Path::~Path()
{
}
