#include "CUL/Filesystem/Path.hpp"
#include "CUL/Time.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Filesystem/FSApi.hpp"

#include "CUL/CULInterface.hpp"

#include "Filesystem/FSUtils.hpp"

using namespace CUL;
using namespace FS;

Path::Path() noexcept
{
}

Path::Path( const Path& path ) noexcept
    : m_isDir( path.m_isDir ),
      m_fullPath( path.m_fullPath ),
      m_extension( path.m_extension ),
      m_baseName( path.m_baseName ),
      m_dir( path.m_dir ),
      m_diskName( path.m_diskName )
{
    normalizePaths();
}

Path::Path( Path&& path ) noexcept
    : m_isDir( path.m_isDir ),
      m_fullPath( std::move( path.m_fullPath ) ),
      m_extension( std::move( path.m_extension ) ),
      m_baseName( std::move( path.m_baseName ) ),
      m_dir( std::move( path.m_dir ) ),
      m_diskName( path.m_diskName )
{
    normalizePath( m_fullPath );
    normalizePaths();
}

Path::Path( const String& inPath ) noexcept
{
    m_fullPath.createFrom( inPath );

    normalizePath( m_fullPath );
    preparePaths();
    normalizePaths();
}

Path::Path( const std::string& path ) noexcept: m_fullPath( path )
{
    normalizePath( m_fullPath );
    preparePaths();
    normalizePaths();
}

Path::Path( const char* r ) noexcept: m_fullPath( r )
{
    normalizePath( m_fullPath );
    preparePaths();
}

Path::Path( const StringWr& inArg ): m_fullPath( inArg )
{
    normalizePath( m_fullPath );
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

Path& Path::operator=( Path&& path ) noexcept
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
    if( !m_fullPath.equals( path.getString().c_str() ) )
    {
        m_fullPath = path.getString();
        preparePaths();
    }
    return *this;
}

Path& Path::operator=( const char* r )
{
    if( !m_fullPath.equals( r ) )
    {
        m_fullPath = r;
        preparePaths();
    }
    return *this;
}

Path& Path::operator=( const std::string& rhv )
{
    if( !m_fullPath.equals( rhv ) )
    {
        m_fullPath = rhv;
        preparePaths();
    }
    return *this;
}

Path& Path::operator+=( const Path& rhv )
{
    m_fullPath.append( rhv.m_fullPath.getValue() );
    preparePaths();
    return *this;
}

Path& Path::operator+=( const String& rhv )
{
    m_fullPath.append( rhv.getString() );
    preparePaths();
    return *this;
}

Path& Path::operator+=( const std::string& rhv )
{
    m_fullPath.append( rhv );
    preparePaths();
    return *this;
}

Path Path::operator+( const Path& rhv )
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

void Path::createFrom( const STDStringWrapper& inArg )
{
    m_fullPath = inArg.getValue();
    preparePaths();
}

const STDStringWrapper& Path::getPath() const
{
    return m_fullPath;
}

const STDStringWrapper& Path::getExtension() const
{
    return m_extension;
}

const STDStringWrapper& Path::getBaseName() const
{
    return m_baseName;
}

const STDStringWrapper& Path::getDir() const
{
    return m_dir;
}

bool Path::isRootOf( const Path& inPath ) const
{
    return inPath.m_dir.contains( m_dir );
}

const STDStringWrapper& Path::getDiskName() const
{
    return m_diskName;
}

uint64_t Path::getFileSize() const
{
    auto calculateSize = [this]()
    {
        const FsPath file( m_fullPath.getValue() );
#if defined( _MSC_VER ) && _MSC_VER < 1920
        m_fileSize = std::experimental::filesystem::file_size( file );
#else
        m_fileSize = std::filesystem::file_size( file );
#endif
        m_sizeCalculated = true;
    };

    if( m_sizeCalculated )
    {
        Time lastModTime;
        getLastModificationTime( lastModTime );
        auto lastModTimeString = lastModTime.toString();
        if( !m_modTime.equals( lastModTimeString.getString() ) )
        {
            calculateSize();
        }
    }
    else
    {
        calculateSize();
    }

    return m_fileSize;
}

void Path::setFileSize( uint64_t inFileSize )
{
    m_fileSize = inFileSize;
}

const STDStringWrapper& Path::getMd5() const
{
    auto calculateMd5 = [this]()
    {
        std::unique_ptr<CUL::FS::IFile> file;

        auto m_culInterface = CUL::CULInterface::getInstance();

        file.reset( m_culInterface->getFF()->createRegularFileRawPtr( *this ) );
        m_md5 = file->getMD5();
    };

    if( m_md5.empty() )
    {
        calculateMd5();
    }
    else
    {
        Time lastModTime;
        getLastModificationTime( lastModTime );
        const String lastModTimeString = lastModTime.toString();
        if( !m_modTime.equals( lastModTimeString.getString() ) )
        {
            calculateMd5();
            m_modTime = lastModTimeString.getString();
        }
    }

    return m_md5;
}

void Path::setMd5( const String& inMD5 )
{
    m_md5 = inMD5.getString();
}

void Path::getLastModificationTime( Time& timeOut ) const
{
    std::unique_ptr<CUL::FS::IFile> file;

    auto m_culInterface = CUL::CULInterface::getInstance();

    file.reset( m_culInterface->getFF()->createRegularFileRawPtr( *this ) );
    file->getLastModificationTime( timeOut );
}

void Path::setModTime( const String& inModTime )
{
    m_modTime = inModTime.getString();
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
    return m_fullPath.getValue() > rhv.m_fullPath.getValue();
}

Path::operator const STDStringWrapper() const
{
    return m_fullPath;
}

void Path::preparePaths()
{
    if( m_fullPath.empty() )
    {
        return;
    }

    const FsPath bPath( m_fullPath.getValue() );
#if CUL_USE_WCHAR
    m_baseName = bPath.stem();
    m_extension = bPath.extension();
    const auto dot = m_extension[0];
    if( dot == L'.' )
    {
        m_extension.erase( 0, 1 );
    }

    std::error_code ec;
    m_isDir = FSCpp::is_directory( bPath, ec );

    const std::string fullPathStdString = m_fullPath.getSTDString();
    const auto errorCodeValue = ec.value();
    if( errorCodeValue == 0 )
    {
        // OK
    }
    else if( errorCodeValue == 1 )
    {
        // The system cannot find the path specified.
        const std::string errorMessage = ec.message();
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "[Path::preparePaths] %s [%s][%d]", errorMessage.c_str(),
                                                 fullPathStdString.c_str(), errorCodeValue );
    }
    else if( errorCodeValue == 2 )
    {
        // The system cannot find the file specified.
        const std::string errorMessage = ec.message();
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "[Path::preparePaths] %s [%s][%d]", errorMessage.c_str(),
                                                 fullPathStdString.c_str(), errorCodeValue );
    }
    else if( errorCodeValue == 3 )
    {
        // The system cannot find the path specified.
        const std::string errorMessage = ec.message();
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "[Path::preparePaths] %s [%s][%d]", errorMessage.c_str(),
                                                 fullPathStdString.c_str(), errorCodeValue );
    }
    else if( errorCodeValue == 123 )
    {
        // The filename, directory name, or volume label syntax is incorrect, propably containing unkown character in path.
        const std::string errorMessage = ec.message();
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "[Path::preparePaths] %s [%s][%d]", errorMessage.c_str(),
                                                 fullPathStdString.c_str(), errorCodeValue );
    }
    else if( errorCodeValue == 1920 )
    {
        // The file cannot be accessed by the system..
        const std::string errorMessage = ec.message();
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "[Path::preparePaths] %s [%s][%d]", errorMessage.c_str(),
                                                 fullPathStdString.c_str(), errorCodeValue );
    }
    else
    {
        const std::string errorMessage = ec.message();
        CUL::Assert::check( false, "%s", errorMessage.c_str() );
    }

    if( m_isDir )
    {
        m_dir = bPath;
    }
    else
    {
        m_dir = bPath.parent_path();
    }
#else
    auto bPathAsString = bPath.string();

    auto stem = bPath.stem();
    m_baseName = stem.c_str();
    auto extension = bPath.extension();
    m_extension = extension.c_str();
    const auto dot = m_extension[0];
    if( dot == '.' )
    {
        m_extension.erase( 0, 1 );
    }

    auto parentPath = bPath.parent_path();
    auto parentPathAsString = parentPath.string();

    m_dir = parentPathAsString;

    m_isDir = FSCpp::is_directory( bPath );
    if( m_isDir )
    {
        m_dir = bPath;
    }
    else
    {
        m_dir = parentPathAsString;
    }
#endif

#if defined( CUL_WINDOWS )
    std::int32_t it = m_dir.find( ":\\" );
    if( it != -1 )
    {
        m_diskName = m_dir.substr( 0, it + 1 );
    }
    else
    {
        it = m_dir.find( ":/" );
        if( it != -1 )
        {
            m_diskName = m_dir.substr( 0, it + 1 );
        }
    }
#else
#endif

    normalizePaths();
}

void Path::normalizePaths()
{
    normalizePath( m_fullPath );
    normalizePath( m_dir );
}

void Path::normalizePath( STDStringWrapper& path )
{
    if( path.empty() )
    {
        return;
    }

#if defined( CUL_WINDOWS )
    path.replace( L'\\', L'/', true );
#else
    path.replace( '\\', '/', true );
#endif
}

bool Path::exists() const
{
    const std::filesystem::path pathAsStdPath = m_fullPath.getValue();
    std::error_code outErrorCode;
    bool result = std::filesystem::is_regular_file( pathAsStdPath, outErrorCode );
    FSApi::handleErrorCode( outErrorCode, m_fullPath.getSTDString().c_str() );
    return result;
}

bool Path::getIsEmpty() const
{
    return m_fullPath.empty();
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
