#pragma once

#include "CUL/Filesystem/FS.hpp"

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4251)
#endif
NAMESPACE_BEGIN( CUL )

class Time;

NAMESPACE_BEGIN( FS )

class CULLib_API Path
{
public:
    Path() noexcept;
    Path( const Path& path ) noexcept;
    Path( Path&& path ) noexcept;
    Path( const String& path ) noexcept;
    Path( const std::string& path ) noexcept;
    Path( const char* r ) noexcept;

    Path& operator=( const Path& path );
    Path& operator=( Path&& path ) noexcept;

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
    void setFileSize( uint64_t inFileSize );

    const String& getMd5() const;
    void setMd5( const String& inMD5 );

    void getLastModificationTime(Time& timeOut) const;
    void setModTime( const String& inModTime );

    void setIsDir(bool isDir);
    bool getIsDir() const;

    bool operator==( const Path& rhv ) const;
    bool operator!=( const Path& rhv ) const;
    bool operator<( const Path& rhv ) const;
    bool operator>( const Path& rhv ) const;

    operator const String() const;

    bool exists() const;
    bool getIsEmpty() const;

    virtual ~Path();

protected:
private:
    void preparePaths();
    void normalizePaths();
    void normalizePath( String& path );

    bool m_isDir = false;
    mutable bool m_sizeCalculated = false;

    String m_fullPath;
    String m_extension;
    String m_baseName;
    String m_dir;

    mutable String m_modTime;

    mutable uint64_t m_fileSize = 0u;
    mutable String m_md5;

    #if defined( CUL_WINDOWS )
    static constexpr String::UnderlyingChar DefaultDirSeparator{ L'\\' };
    static constexpr String::UnderlyingChar ExtensionSeparator{ L'.' };
    #else // #if defined(CUL_WINDOWS)
    static constexpr String::UnderlyingChar DefaultDirSeparator{ '/' };
    static constexpr String::UnderlyingChar ExtensionSeparator{ '.' };
    #endif // #if defined(CUL_WINDOWS)
};

const Path CULLib_API operator+( const Path& lval, const Path& rval );
NAMESPACE_END( FS )
NAMESPACE_END( CUL )

#if _MSC_VER
#pragma warning( pop )
#endif