#pragma once
#include "CUL/CUL.hpp"
#include "CUL/MyString.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4251)
#endif
NAMESPACE_BEGIN( CUL )
using CBool = const bool;
NAMESPACE_BEGIN( FS )
class CULLib_API Path
{
public:
    Path();
    Path( const Path& path );
    Path( CnstMyStr& path );
    Path( const char* r );
    virtual ~Path();

    Path& operator=( CnstMyStr& r );
    Path& operator=( const char* r );
    Path& operator+=( const Path& rhv );
    Path& operator+=( CnstMyStr& rhv );

    Path operator+( const Path& rhv );
	Path operator+( CnstMyStr& rhv );
	Path operator+( const char* rhv );

    CnstMyStr& getPath()const;
    CnstMyStr& getExtension()const;
    CnstMyStr& getBaseName()const;
    CnstMyStr& getDir()const;

    const bool operator==( const Path& rhv ) const;

    operator CnstMyStr() const;

    const bool exists()const;

    static CnstMyStr& getDirSeparator();

protected:
private:
    void preparePaths();
    void normalizePaths();
    void normalizePath( MyString& path );

    MyString m_fullPath;
    MyString m_extension;
    MyString m_baseName;
    MyString m_dir;

    static MyString extensionSeparator;
};

const bool CULLib_API operator<( const Path& lhv, const Path& rhv );
const Path CULLib_API operator+( const Path& lval, const Path& rval );
NAMESPACE_END( FS )
NAMESPACE_END( CUL )
#if _MSC_VER
#pragma warning( pop )
#endif