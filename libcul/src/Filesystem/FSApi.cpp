#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/CULInterface.hpp"

#include "CUL/IMPORT_tracy.hpp"

#include "CUL/STL_IMPORTS/STD_exception.hpp"
#include "CUL/STL_IMPORTS/STD_filesystem.hpp"

using namespace CUL;
using namespace FS;

FSApi::FSApi( CULInterface* cul, FS::FileFactory* ff ) :
    m_culInterface( cul ),
    m_fileFactory( ff )
{
}

std::vector<Path> FSApi::ListAllFiles( const Path& directory )
{
    ZoneScoped;
    std::vector<Path> result;

    for( const auto& entry : std::filesystem::recursive_directory_iterator( directory.getPath().string(), std::filesystem::directory_options::skip_permission_denied ) )
    {
        const std::filesystem::path entryPath = entry.path();

#ifdef _MSC_VER
        String temp = entryPath.wstring();
        Path culPath = temp;
#else
        Path culPath = entryPath.string();
#endif
        bool isDir = isDirectory( culPath );
        culPath.setIsDir( isDir );

        result.push_back( culPath );
    }

    return result;
}

void FSApi::ListAllFiles( const Path& directory, std::function<void( const Path& path )> callback )
{
    ZoneScoped;
    std::vector<Path> result;

    const auto dir = directory.getPath().string();
    std::error_code errorCode;
    for( const auto& entry :
         std::filesystem::recursive_directory_iterator( dir, std::filesystem::directory_options::skip_permission_denied, errorCode ) )
    {
        ZoneScoped;
        if( errorCode.value() != 0 )
        {
            CUL::Assert::check( false, errorCode.message().c_str() );
        }

        const std::filesystem::path entryPath = entry.path();
        const String tempString = entryPath.c_str();

        const std::u32string someString = entryPath.u32string();
#ifdef _MSC_VER
        const String tempPath = entryPath.wstring();
        Path culPath = tempPath;
#else
        Path culPath = entryPath.string();
#endif
        bool isDir = isDirectory( culPath );
        culPath.setIsDir( isDir );

        callback( culPath );
    }
}

void FSApi::deleteFile( const Path& path )
{
    std::error_code ec;
    const std::filesystem::path target = path.getPath().getChar();

    std::filesystem::remove( target, ec );

    static std::error_condition ok;
    if( ec != ok )
    {
        const auto messageStr = ec.message();
        const char* msg = messageStr.c_str();
        LOG::ILogger::getInstance().logVariable( CUL::LOG::Severity::ERROR, "FSApi::DeleteFile error: [%s]", msg );
    }
}

bool FSApi::isDirectory( const Path& path )
{
#ifdef FILESYSTEM_IS_EXPERIMENTAL
    return std::experimental::filesystem::is_directory( path );
#else
    std::error_code ec;
    bool result = std::filesystem::is_directory( path.getPath().getChar(), ec );
    return result;
#endif
}

void FSApi::getCreationTime( const Path&, Time& )
{
    throw std::logic_error( "Method not implemented" );
}

template <typename TP>
std::time_t to_time_t( TP tp )
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>( tp - TP::clock::now() + system_clock::now() );
    return system_clock::to_time_t( sctp );
}

void FSApi::getLastModificationTime( const Path& inPath, Time& outTime )
{
    ZoneScoped;
    if( false == m_culInterface->getFS()->fileExist( inPath ) )
    {
        return;
    }

    std::filesystem::path p = inPath.getPath().getChar();
    std::filesystem::file_time_type ftime = std::filesystem::last_write_time( p );

    const std::uint64_t timeConverted = static_cast<std::uint64_t>( to_time_t( ftime ) );
    outTime.setTimeSec( timeConverted );
}

bool FSApi::fileExist( const Path& path )
{
    return isRegularFile( path );
}

String FSApi::getCurrentDir()
{
    auto currentDir = std::filesystem::current_path();
    const std::filesystem::path full_path( currentDir );
    return full_path.string();
}

IFile* FSApi::getDirectory( const Path& directory )
{
    ZoneScoped;
    Directory* result = new Directory( directory, m_culInterface );
    const auto inPath = directory.getPath().getChar();
    std::filesystem::path directoryBf( inPath );
    using DI = std::filesystem::directory_iterator;
    DI end;
    for( DI it( directoryBf ); it != end; ++it )
    {
        ZoneScoped;
        const auto& pathIt = it->path();
        const auto filePath = pathIt.string();
        if( isRegularFile( filePath ) )
        {
            auto child = m_fileFactory->createFileFromPath( filePath );
            result->addChild( child );
        }
        else if( isDirectory( filePath.c_str() ) )
        {
            auto nestedDirectory = getDirectory( filePath );
            result->addChild( nestedDirectory );
        }
    }

    return result;
}

bool FSApi::isRegularFile( const String& path )
{
    std::error_code existsErrorCode;
    bool result = std::filesystem::is_regular_file( path.getChar(), existsErrorCode );
    if( existsErrorCode.value() != 0 )
    {
        LOG::ILogger::getInstance().logVariable( CUL::LOG::Severity::ERROR, "[%s] %s", path.getChar(), existsErrorCode.message().c_str() );
    }
    return result;
}

String FSApi::getFileSize( const Path& path )
{
    std::error_code ec;

#ifdef _MSC_VER
    const std::filesystem::path filePath = path.getPath().wstring();
    uintmax_t size = std::filesystem::file_size( filePath, ec );

    if( ec.value() != 0 )
    {
        const auto message = ec.message();
        LOG::ILogger::getInstance().log( message );

        std::error_code symlinkCheckError;
        if( std::filesystem::is_symlink( filePath, symlinkCheckError ) )
        {
            size = 0u;
        }
        else
        {
            std::error_code isRegularFileCheck;
            if( std::filesystem::is_regular_file( filePath, isRegularFileCheck ) == false )
            {
                size = 0u;
            }
            else
            {
                CUL::Assert::check( false, isRegularFileCheck.message().c_str() );
            }
        }
    }
#else
    uintmax_t size = std::filesystem::file_size( path.getPath().string(), ec );
#endif

    const auto string = std::to_string( size );
    String result = string;
    return result;
}

FSApi::~FSApi()
{
}