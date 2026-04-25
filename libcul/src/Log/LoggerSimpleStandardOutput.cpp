#include "Log/LoggerSimpleStandardOutput.hpp"
#include "IMPORT_spdlog.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/IMPORT_windows.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_cstdarg.hpp"

#undef ERROR

using namespace CUL;
using namespace LOG;

LoggerSimpleStandardOutput::LoggerSimpleStandardOutput()
    : m_interface( *CUL::CULInterface::getInstance() )
    , m_variableBuffer{}
{
    init();
}

void LoggerSimpleStandardOutput::log( const String& text, const Severity severity )
{
    log( text.getChar(), severity );
}

const std::string currentDateTime()
{
    time_t now = time( 0 );
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime( &now );
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime( buf, sizeof( buf ), "%Y-%m-%d_%X", &tstruct );

    return buf;
}

std::shared_ptr<spdlog::logger> g_fileLogger;

void LoggerSimpleStandardOutput::init()
{
    CUL::CULInterface::getInstance();

#if defined( CUL_WINDOWS )
    auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
    m_logger = std::make_shared<spdlog::logger>( "win logger", std::move( sink ) );
#else
    m_logger = spdlog::default_logger();
#endif

    const std::string dateTime = currentDateTime();
    const char* baseName = "LOG_";
    StringWr fileName = StringWr::createFromPrintf( "%s%s.log", baseName, dateTime.c_str() );
    fileName.removeAll( ':' );
    fileName.removeAll( '-' );

    g_fileLogger = spdlog::basic_logger_mt( "file_logger", fileName.getValue() );
    findAndCheckOldestLogFiles( baseName );
}

void LoggerSimpleStandardOutput::findAndCheckOldestLogFiles( const CUL::String& inLogBaseName )
{
    const auto currentDir = m_interface.getFS()->getCurrentDir(); 
    std::vector<FS::Path> listOfFiles =
        m_interface.getFS()->ListAllFiles( currentDir, *inLogBaseName );

    const std::int32_t howManyToDelete =
        static_cast<std::int32_t>( listOfFiles.size() ) - m_maxLogCount;

    if( howManyToDelete <= 0 )
    {
        return;
    }

    std::sort( listOfFiles.begin(),
               listOfFiles.end(),
               [](const FS::Path& p1, const FS::Path& p2)
               {
                   return p1.getPath().getValue() < p2.getPath().getValue();
               } );

    for( std::int32_t i = 0; i < howManyToDelete; ++i )
    {
        m_interface.getFS()->deleteFile( listOfFiles[i] );
    }
}

void LoggerSimpleStandardOutput::logInfo( const char* msg... )
{
    va_list args;
    va_start( args, msg );
    std::lock_guard<std::mutex> locker( m_variableMutex );
    vsnprintf( m_variableBuffer, s_bufferSize, msg, args );
    log( m_variableBuffer, Severity::Info );
    va_end( args );
}

void LoggerSimpleStandardOutput::logVariable( Severity severity, const char* msg... )
{
    va_list args;
    va_start( args, msg );
    std::lock_guard<std::mutex> locker( m_variableMutex );
    vsnprintf( m_variableBuffer, s_bufferSize, msg, args );
    log( m_variableBuffer, severity );
    va_end( args );
}

void LoggerSimpleStandardOutput::log( const char* message, const Severity severity )
{
    switch( severity )
        case Severity::Critical:
    {
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->critical( message );
            g_fileLogger->critical( message );
            break;
        }
        case Severity::Error:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->error( message );
            g_fileLogger->error( message );
            break;
        }
        case Severity::Warn:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->warn( message );
            g_fileLogger->warn( message );
            break;
        }
        case Severity::Info:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->info( message );
            g_fileLogger->info( message );
            break;
        }
        default:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->info( message );
            g_fileLogger->info( message );
        }
    }
}

void LoggerSimpleStandardOutput::log( const wchar_t* message, const Severity severity )
{
// [Bartlomiej.Kordek] spdlog does not support wchar on linux ecosystem.
#if CUL_USE_WCHAR
    switch( severity )
    {
        case Severity::Critical:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->critical( message );
            g_fileLogger->critical( message );
            break;
        }
        case Severity::Error:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->error( message );
            g_fileLogger->error( message );
            break;
        }
        case Severity::Warn:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->warn( message );
            g_fileLogger->warn( message );
            break;
        }
        case Severity::Info:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->info( message );
            g_fileLogger->info( message );
            break;
        }
        default:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->info( message );
            g_fileLogger->info( message );
        }
    }
#endif  // CUL_USE_WCHAR
}

LoggerSimpleStandardOutput::~LoggerSimpleStandardOutput()
{
    log( "Destroying LoggerSimpleStandardOutput... Done." );
}