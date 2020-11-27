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
    Path( Path&& path );
    Path( const String& path );
    Path( const std::string& path );
    Path( const char* r );

    Path& operator=( const Path& path );
    Path& operator=( Path&& path );

    Path& operator=( const String& r );
    Path& operator=( const char* r );
    Path& operator=( const std::string& rhv );
    Path& operator+=( const Path& rhv );
    Path& operator+=( const String& rhv );
    Path& operator+=( const std::string& rhv );

    Path operator+( const Path& rhv );
    Path operator+( const String& rhv );
    Path operator+( const char* rhv );

    const String& getPath() const;
    const String& getExtension() const;
    const String& getBaseName() const;
    const String& getDir() const;

    uint64_t getFileSize() const;

    bool operator==( const Path& rhv ) const;
    bool operator!=( const Path& rhv ) const;
    bool operator<( const Path& rhv ) const;
    bool operator>( const Path& rhv ) const;

    operator const String() const;

    bool exists() const;

    static const String& getDirSeparator();

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

const Path CULLib_API operator+( const Path& lval, const Path& rval );
NAMESPACE_END( FS )
NAMESPACE_END( CUL )

#if _MSC_VER
#pragma warning( pop )
#endif
