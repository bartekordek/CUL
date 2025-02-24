#include "Log/LoggerSimpleStandardOutput.hpp"
#include "IMPORT_spdlog.hpp"
#include "CUL/IMPORT_windows.hpp"
#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_cstdarg.hpp"

#undef ERROR

using namespace CUL;
using namespace LOG;

LoggerSimpleStandardOutput::LoggerSimpleStandardOutput() : m_variableBuffer{}
{
    init();
}

void LoggerSimpleStandardOutput::log( const String& text, const Severity severity )
{
    log( text.getChar(), severity );
}

void LoggerSimpleStandardOutput::init()
{
#if defined( CUL_WINDOWS )
    auto sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
    m_logger = std::make_shared<spdlog::logger>( "win logger", std::move( sink ) );
#else
    m_logger = spdlog::default_logger();
#endif
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
            break;
        }
        case Severity::Error:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->error( message );
            break;
        }
        case Severity::Warn:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->warn( message );
            break;
        }
        case Severity::Info:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->info( message );
            break;
        }
        default:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->info( message );
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
            break;
        }
        case Severity::Error:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->error( message );
            break;
        }
        case Severity::Warn:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->warn( message );
            break;
        }
        case Severity::Info:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->info( message );
            break;
        }
        default:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            m_logger->info( message );
        }
    }
#endif  // CUL_USE_WCHAR
}

LoggerSimpleStandardOutput::~LoggerSimpleStandardOutput()
{
    log( "Destroying LoggerSimpleStandardOutput... Done." );
}