#pragma once

#include "CUL/CUL.hpp"
#include "CUL/MyString.hpp"

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4251)
#endif

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

using CBool = const bool;
using CstString = const std::string;
class CULLib_API Path
{
public:
    Path();
    Path( const Path& path );
    Path( CstString& path );
    Path( const char* r );
    virtual ~Path();

    Path& operator=( CstString& r );
    Path& operator=( const char* r );
    Path& operator+( const Path& rhv );
    Path& operator+( CstString& rhv );

    CstString& getPath()const;
    CstString& getExtension()const;
    CstString& getBaseName()const;
    CstString& getDir()const;

    const bool exists()const;

    static CstString& getDirSeparator();
protected:
private:
    void preparePaths();
    CUL::MyString fullPath;
    CUL::MyString extension;
    CUL::MyString baseName;
    CUL::MyString dir;

    static CUL::MyString directorySeparator;
    static CUL::MyString extensionSeparator;
};

Path CULLib_API operator+( const Path& l, CstString& r );
Path CULLib_API operator+( const Path& l, const Path& r );

NAMESPACE_END( FS )
NAMESPACE_END( CUL )

#if _MSC_VER
#pragma warning( pop )
#endif