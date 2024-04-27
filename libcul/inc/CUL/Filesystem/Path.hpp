#pragma once

#include "CUL/Filesystem/FS.hpp"
#include "CUL/TimeConcrete.hpp"
#include "CUL/StrintUTF.hpp"

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4251)
#endif
NAMESPACE_BEGIN( CUL )
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

    Path& operator=( const StringUTF& r );
    Path& operator=( const char* r );
    Path& operator=( const std::string& rhv );
    Path& operator+=( const Path& rhv );
    Path& operator+=( const StringUTF& rhv );
    Path& operator+=( const std::string& rhv );

    Path operator+( const Path& rhv );
    Path operator+( const StringUTF& rhv );
    Path operator+( const char* rhv );

    const StringUTF& getPath() const;
    const StringUTF& getExtension() const;
    const StringUTF& getBaseName() const;
    const StringUTF& getDir() const;

    std::uint64_t getFileSize() const;
    void setFileSize( std::uint64_t inFileSize );

    const String& getMd5() const;
    void setMd5( const String& inMD5 );

    TimeConcrete getLastModificationTime() const;
    void setModTime( const StringUTF& inModTime );

    void setIsDir(bool isDir);
    bool getIsDir() const;

    bool operator==( const Path& rhv ) const;
    bool operator!=( const Path& rhv ) const;
    bool operator<( const Path& rhv ) const;
    bool operator>( const Path& rhv ) const;

    bool exists() const;

    static const StringUTF& getDirSeparator();

    virtual ~Path();

protected:
private:
    void preparePaths();
    void normalizePaths();
    void normalizePath( StringUTF& path );

    bool m_isDir = false;
    mutable bool m_sizeCalculated = false;

    StringUTF m_fullPath;
    StringUTF m_extension;
    StringUTF m_baseName;
    StringUTF m_dir;

    StringUTF m_modTime;

    mutable std::uint64_t m_fileSize = 0u;
    mutable StringUTF m_md5;

    static StringUTF extensionSeparator;
};

const Path CULLib_API operator+( const Path& lval, const Path& rval );
NAMESPACE_END( FS )
NAMESPACE_END( CUL )

#if _MSC_VER
#pragma warning( pop )
#endif