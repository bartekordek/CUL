#include "CUL/Path.hpp"
#include "BoostFilesystem.hpp"
#include "STDCodecvt.hpp"

using namespace CUL;
using namespace FS;

MyString ws2s( const std::wstring& wstr );

#ifdef _WIN32
MyString Path::directorySeparator = MyString( "\\" );
#else
MyString Path::directorySeparator = MyString( "/" );
#endif
MyString Path::extensionSeparator = MyString( "." );

CnstMyStr& Path::getDirSeparator()
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

Path::Path( CnstMyStr& path ):
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

Path& Path::operator=( CnstMyStr& path )
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

Path& Path::operator+=( const Path& rhv )
{
    this->fullPath = this->fullPath + rhv.fullPath;
    preparePaths();
    return *this;
}

Path& Path::operator+=( CnstMyStr& rhv )
{
    this->fullPath = this->fullPath + rhv;
    preparePaths();
    return *this;
}

CnstMyStr& Path::getPath()const
{
    return this->fullPath;
}

CnstMyStr& Path::getExtension()const
{
    return this->extension;
}

CnstMyStr& Path::getBaseName()const
{
    return this->baseName;
}

CnstMyStr& Path::getDir()const
{
    return this->dir;
}

void Path::preparePaths()
{
    boost::filesystem::path bPath( this->fullPath.cStr() );
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

MyString ws2s( const std::wstring& wstr )
{
    using convert_typeX = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_typeX, wchar_t> converterX;

    return converterX.to_bytes( wstr );
}

const bool Path::exists() const
{
    const bool result = boost::filesystem::is_regular_file( this->fullPath.cStr() );
    return result;
}
/*
Path CUL::FS::operator+( const Path& l, CnstMyStr& r )
{
    Path result( l.getPath() + r );
    return result;
}

Path operator+( const Path& l, const Path& r )
{
    Path result( l.getPath() + r.getPath() );
    return result;
}
*/
