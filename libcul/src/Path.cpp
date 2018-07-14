#include "CUL/Path.hpp"
#include "BoostFilesystem.hpp"
#include "STDCodecvt.hpp"

using namespace CUL;
using namespace FS;

std::string ws2s( const std::wstring& wstr );

#ifdef _WIN32
std::string Path::directorySeparator = std::string( "\\" );
#else
std::string Path::directorySeparator = std::string( "/" );
#endif
std::string Path::extensionSeparator = std::string( "." );

CstString& Path::getDirSeparator()
{
    return extensionSeparator;
}

Path::Path()
{

}

Path::Path( const Path& path ): 
    fullPath( path.fullPath ),
    extension( path.extension ),
    baseName( path.baseName ),
    dir( path.dir )
{
}

Path::Path( CstString& path ):
    fullPath(path)
{
    preparePaths();
}

Path::Path( const char* r ):
    fullPath( r )
{
    preparePaths();
}

Path::~Path()
{

}

Path& Path::operator=( CstString& path )
{
    if( this->fullPath != path )
    {
        this->fullPath = path;
        preparePaths();
    }
    return *this;
}

Path& Path::operator=( const char* r )
{
    if ( this->fullPath != r )
    {
        this->fullPath = r;
        preparePaths();
    }
    return *this;
}

Path& Path::operator+( const Path& rhv )
{
    this->fullPath = this->fullPath + rhv.fullPath;
    preparePaths();
    return *this;
}

Path& Path::operator+( CstString& rhv )
{
    this->fullPath = this->fullPath + rhv;
    preparePaths();
    return *this;
}

CstString& Path::getPath()const
{
    return this->fullPath;
}

CstString& Path::getExtension()const
{
    return this->extension;
}

CstString& Path::getBaseName()const
{
    return this->baseName;
}

CstString& Path::getDir()const
{
    return this->dir;
}

void Path::preparePaths()
{
    boost::filesystem::path bPath( this->fullPath );
#if defined CUL_WINDOWS
    this->baseName = ws2s( bPath.stem().c_str() );
    this->extension = ws2s( bPath.extension().c_str() );
    this->dir = ws2s( bPath.parent_path().c_str() );
#else
    this->baseName = bPath.stem().c_str();
    this->extension = bPath.extension().c_str();
    this->dir = bPath.parent_path().c_str();
#endif
}

std::string ws2s( const std::wstring& wstr )
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes( wstr );
}

const bool Path::exists() const
{
    const bool result = boost::filesystem::is_regular_file( this->fullPath );
    return result;
}

Path operator+( const Path& l, const std::string& r )
{
    Path result( l.getPath() + r );
    return result;
}

Path operator+( const Path& l, const Path& r )
{
    Path result( l.getPath() + r.getPath() );
    return result;
}