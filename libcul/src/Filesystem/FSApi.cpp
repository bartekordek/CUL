#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/Proifling/Profiler.hpp"

#include "CUL/STL_IMPORTS/STD_exception.hpp"
#include <CUL/STL_IMPORTS/STD_chrono.hpp>

using namespace CUL;
using namespace FS;

FSApi::FSApi( CULInterface* cul, FS::FileFactory* ff ): m_culInterface( cul ), m_fileFactory( ff )
{
}

std::vector<Path> FSApi::ListAllFiles( const Path& directory )
{
    ProfilerScope( "FSApi::ListAllFiles" );

    std::vector<Path> result;

    const std::filesystem::path dirAsPath = directory.getPath().getValue();
    for( const auto& entry :
         std::filesystem::recursive_directory_iterator( dirAsPath, std::filesystem::directory_options::skip_permission_denied ) )
    {
        const std::filesystem::path entryPath = entry.path();
        std::error_code ec;
        Path culPath;
        culPath.createFrom( StringWr( entryPath.c_str() ) );
        result.push_back( culPath );
    }

    return result;
}

void FSApi::ListAllFiles( const Path& directory, std::function<void( const Path& path )> callback )
{
    ProfilerScope( "FSApi::ListAllFiles" );

    const auto dir = directory.getPath().getValue();
    const auto directoryOptions = std::filesystem::directory_options::skip_permission_denied;
    std::error_code ec;
    const std::filesystem::directory_iterator dirIt = std::filesystem::directory_iterator( dir, directoryOptions, ec );
    for( const std::filesystem::directory_entry& it : dirIt )
    {
        iterateThrought( it, callback );
    }
}

void FSApi::iterateThrought( const std::filesystem::directory_entry& de, std::function<void( const Path& path )> callback )
{
    ProfilerScope( "FSApi::iterateThrought" );

    const std::filesystem::path entryPath = de.path();

#ifdef _MSC_VER
    const String tempPath = entryPath.wstring();
    Path culPath = tempPath;
#else
    Path culPath = entryPath.string();
#endif

    std::error_code ec;
    if( de.is_regular_file( ec ) )
    {
        culPath.setIsDir( false );
        callback( culPath );
    }
    else
    {
        ListAllFiles( culPath, callback );
    }

    handleErrorCode( ec, culPath.getPath().getUtfChar() );
}

void FSApi::handleErrorCode( const std::error_code& ec, const char* inPath )
{
    ProfilerScope( "FSApi::handleErrorCode ec inPath" );

    const auto errorCodeValue = ec.value();
    if( errorCodeValue == 0 )
    {
        // OK
    }
    else if( errorCodeValue > 1 && errorCodeValue < 4 )
    {
        // The system cannot find the path specified.
        const std::string errorMessage = ec.message();
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "[Path::preparePaths] %s [%s][%d]", errorMessage.c_str(), inPath,
                                                 errorCodeValue );
    }
    else if( errorCodeValue == 1920 )
    {
        // The file cannot be accessed by the system..
        const std::string errorMessage = ec.message();
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "[Path::preparePaths] %s [%s][%d]", errorMessage.c_str(), inPath,
                                                 errorCodeValue );
    }
    else
    {
        const std::string errorMessage = ec.message();
        CUL::Assert::check( false, "%s", errorMessage.c_str() );
    }
}

void FSApi::deleteFile( const Path& path )
{
    ProfilerScope( "FSApi::deleteFile" );

    std::error_code ec;
    const std::filesystem::path target = path.getPath().getValue();

    std::filesystem::remove( target, ec );

    static std::error_condition ok;
    if( ec != ok )
    {
        const auto messageStr = ec.message();
        const char* msg = messageStr.c_str();
        LOG::ILogger::getInstance().logVariable( CUL::LOG::Severity::Error, "FSApi::DeleteFile error: [%s]", msg );
    }
}

bool FSApi::isDirectory( const Path& path )
{
    ProfilerScope( "FSApi::isDirectory" );
    std::error_code ec;
    bool result = std::filesystem::is_directory( path.getPath().getValue(), ec );
    return result;
}

void FSApi::getCreationTime( const Path&, Time& )
{
    throw std::logic_error( "Method not implemented" );
}

std::string getTimeh( const std::chrono::sys_time<std::chrono::system_clock::duration>& duration )
{
    const time_t convertedTimeT = std::chrono::system_clock::to_time_t( duration );
    char buffer[256];

#if defined( CUL_WINDOWS )
    tm timeValue;
    localtime_s( &timeValue, &convertedTimeT );
    std::strftime( buffer, 256, "%Y/%m/%d %H:%M:%S", &timeValue );
#else
    std::strftime( buffer, 256, "%Y/%m/%d %H:%M:%S", std::localtime( &convertedTimeT ) );
#endif

    return std::string( buffer );
}

void FSApi::getLastModificationTime( const Path& inPath, Time& outTime )
{
    ProfilerScope( "FSApi::getLastModificationTime" );
    if( false == m_culInterface->getFS()->fileExist( inPath ) )
    {
        return;
    }

    std::filesystem::path p = inPath.getPath().getValue();
    std::filesystem::file_time_type ftime = std::filesystem::last_write_time( p );
    const std::chrono::sys_time<std::chrono::system_clock::duration> systemTime =
        std::chrono::clock_cast<std::chrono::system_clock>( ftime );
    const time_t convertedTimeT = std::chrono::system_clock::to_time_t( systemTime );

    constexpr std::size_t bufferSize{ 128u };
    char buffer[bufferSize];

    if( convertedTimeT == -1 )
    {
        snprintf( buffer, bufferSize, "1970/1/1 0:0:0" );
    }
    else
    {
#if defined( CUL_WINDOWS )
        tm timeValue;
        localtime_s( &timeValue, &convertedTimeT );
        std::strftime( buffer, bufferSize, "%Y/%m/%d %H:%M:%S", &timeValue );
#else
        std::strftime( buffer, bufferSize, "%Y/%m/%d %H:%M:%S", std::localtime( &convertedTimeT ) );
#endif
    }

    const String st = buffer;
    const std::vector<String> parts = st.split( " " );
    const String date = parts[0];
    const String time = parts[1];

    const std::vector<String> dateSplit = date.split( "/" );

    const std::int32_t year = dateSplit[0].toInt64();
    outTime.setYear( year );

    // Firstly, set the day, because if we have for example February, and previously
    // day was set to 31, it will throw an exception.
    const std::int32_t day = dateSplit[2].toInt64();
    outTime.setDay( day );

    const std::int32_t month = dateSplit[1].toInt64();
    outTime.setMonth( month );

    const std::vector<String> timeSplit = time.split( ":" );
    const std::int32_t hour = timeSplit[0].toInt64();
    outTime.setHour( hour );

    const std::int32_t minute = timeSplit[1].toInt64();
    outTime.setMinute( minute );
    const std::int32_t second = timeSplit[2].toInt64();
    outTime.setSecond( second );
}

bool FSApi::fileExist( const Path& path )
{
    return isRegularFile( path.getPath().getValue() );
}

String FSApi::getCurrentDir()
{
    auto currentDir = std::filesystem::current_path();
    const std::filesystem::path full_path( currentDir );
    return full_path.string();
}

IFile* FSApi::getDirectory( const Path& directory )
{
    ProfilerScope( "FSApi::getDirectory" );
    Directory* result = new Directory( directory, m_culInterface );
    const auto inPath = directory.getPath().getValue();
    std::filesystem::path directoryBf( inPath );
    using DI = std::filesystem::directory_iterator;
    DI end;
    for( DI it( directoryBf ); it != end; ++it )
    {
        ProfilerScope( "FSApi::getDirectory::it" );
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
    ProfilerScope( "FSApi::isRegularFile" );
    std::error_code existsErrorCode;
    const std::filesystem::path filePath = path.getChar();
    const bool result = std::filesystem::is_regular_file( filePath, existsErrorCode );
    if( existsErrorCode.value() != 0 )
    {
        const std::string errorCodeMessageStr = existsErrorCode.message();
        const auto pathString = filePath.string();
        LOG::ILogger::getInstance().logVariable( CUL::LOG::Severity::Error, "FSApi::isRegularFile: [%s] %s", pathString.c_str(),
                                                 errorCodeMessageStr.c_str() );
    }
    return result;
}

String FSApi::getFileSize( const Path& path )
{
    ProfilerScope( "FSApi::getFileSize" );
    std::error_code ec;

#ifdef _MSC_VER
    const std::filesystem::path filePath = path.getPath().getValue();
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
                CUL::Assert::check( false, "%s", isRegularFileCheck.message().c_str() );
            }
        }
    }
#else
    uintmax_t size = std::filesystem::file_size( path.getPath().getValue().c_str(), ec );
#endif

    const auto string = std::to_string( size );
    String result = string;
    return result;
}

FSApi::~FSApi()
{
}
