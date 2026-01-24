#pragma once

#include "CUL/Filesystem/FS.hpp"
#include "CUL/String/StringWrapper.hpp"

#if _MSC_VER
    #pragma warning( push )
    #pragma warning( disable : 4251 )
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
    Path( const StringWr& inArg );

    Path& operator=( const Path& path );
    Path& operator=( Path&& path ) noexcept;

    Path& operator=( const String& r );
    Path& operator=( const char* r );
    Path& operator=( const std::string& rhv );
    Path& operator=( const StringWr& inArg );

    Path& operator+=( const Path& rhv );
    Path& operator+=( const String& rhv );
    Path& operator+=( const std::string& rhv );

    Path operator+( const Path& rhv );
    Path operator+( const String& rhv );
    Path operator+( const char* rhv );

    void createFrom( const STDStringWrapper& inArg );

    const STDStringWrapper& getPath() const;
    const STDStringWrapper& getExtension() const;
    const STDStringWrapper& getBaseName() const;
    const STDStringWrapper& getDir() const;

    uint64_t getFileSize() const;
    void setFileSize( uint64_t inFileSize );

    const STDStringWrapper& getMd5() const;
    void setMd5( const String& inMD5 );

    void getLastModificationTime( Time& timeOut ) const;
    void setModTime( const String& inModTime );

    void setIsDir( bool isDir );
    bool getIsDir() const;

    bool operator==( const Path& rhv ) const;
    bool operator!=( const Path& rhv ) const;
    bool operator<( const Path& rhv ) const;
    bool operator>( const Path& rhv ) const;

    operator const STDStringWrapper() const;

    bool exists() const;
    bool getIsEmpty() const;
    bool isRootOf( const Path& inPath ) const;
    const STDStringWrapper& getDiskName() const;

    virtual ~Path();

protected:
private:
    void preparePaths();
    void normalizePaths();
    void normalizePath( STDStringWrapper& path );

    bool m_isDir = false;
    mutable bool m_sizeCalculated = false;

    STDStringWrapper m_fullPath;
    STDStringWrapper m_extension;
    STDStringWrapper m_baseName;
    STDStringWrapper m_dir;
    STDStringWrapper m_diskName;

    mutable STDStringWrapper m_modTime;

    mutable uint64_t m_fileSize = 0u;
    mutable STDStringWrapper m_md5;

#if defined( CUL_WINDOWS )
    static constexpr String::UnderlyingChar DefaultDirSeparator{ L'\\' };
    static constexpr String::UnderlyingChar ExtensionSeparator{ L'.' };
#else   // #if defined(CUL_WINDOWS)
    static constexpr String::UnderlyingChar DefaultDirSeparator{ '/' };
    static constexpr String::UnderlyingChar ExtensionSeparator{ '.' };
#endif  // #if defined(CUL_WINDOWS)
};

const Path CULLib_API operator+( const Path& lval, const Path& rval );
NAMESPACE_END( FS )
NAMESPACE_END( CUL )

#if _MSC_VER
    #pragma warning( pop )
#endif