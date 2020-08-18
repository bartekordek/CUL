#pragma once
#include "CUL/CUL.hpp"
#include "CUL/String.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4251)
#endif
NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

class CULLib_API Path
{
public:
    Path();
    Path( const Path& path );
    Path( CsStr& path );
    Path( const std::string& path );
    Path( const char* r );

    Path& operator=( CsStr& r );
    Path& operator=( const char* r );
    Path& operator=( const std::string& rhv );
    Path& operator+=( const Path& rhv );
    Path& operator+=( CsStr& rhv );
    Path& operator+=( const std::string& rhv );

    Path operator+( const Path& rhv );
    Path operator+( CsStr& rhv );
    Path operator+( const char* rhv );

    CsStr& getPath() const;
    CsStr& getExtension() const;
    CsStr& getBaseName() const;
    CsStr& getDir() const;

    bool operator==( const Path& rhv ) const;

    operator CsStr() const;

    bool exists() const;

    static CsStr& getDirSeparator();

    virtual ~Path();

protected:
private:
    void preparePaths();
    void normalizePaths();
    void normalizePath( String& path );

    String m_fullPath;
    String m_extension;
    String m_baseName;
    String m_dir;

    static String extensionSeparator;
};

bool CULLib_API operator<( const Path& lhv, const Path& rhv );
const Path CULLib_API operator+( const Path& lval, const Path& rval );
NAMESPACE_END( FS )
NAMESPACE_END( CUL )
#if _MSC_VER
#pragma warning( pop )
#endif
