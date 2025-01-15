#include "Log/LoggerSimpleStandardOutput.hpp"
#include "IMPORT_spdlog.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_cstdarg.hpp"

#undef ERROR

using namespace CUL;
using namespace LOG;

LoggerSimpleStandardOutput::LoggerSimpleStandardOutput(): m_variableBuffer{}
{
}

void LoggerSimpleStandardOutput::log( const String& text, const Severity severity )
{
    log( text.getChar(), severity );
}

void LoggerSimpleStandardOutput::logVariable( Severity severity, const char* msg... )
{
    va_list args;
    va_start( args, msg );
    std::lock_guard<std::mutex> locker( m_variableMutex );
    vsprintf( m_variableBuffer, msg, args );
    log( m_variableBuffer, severity );
    va_end( args );
}

void LoggerSimpleStandardOutput::log( const char* message, const Severity severity )
{
    switch( severity )
    {
        case Severity::CRITICAL:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::critical( message );
            break;
        }
        case Severity::ERROR:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::error( message );
            break;
        }
        case Severity::WARN:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::warn( message );
            break;
        }
        case Severity::INFO:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::info( message );
            break;
        }
        default:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::info( message );
        }
    }
}

void LoggerSimpleStandardOutput::log( const wchar_t* message, const Severity severity )
{
// [Bartlomiej.Kordek] spdlog does not support wchar on linux ecosystem.
#if CUL_USE_WCHAR
    switch( severity )
    {
        case Severity::CRITICAL:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::critical( message );
            break;
        }
        case Severity::ERROR:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::error( message );
            break;
        }
        case Severity::WARN:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::warn( message );
            break;
        }
        case Severity::INFO:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::info( message );
            break;
        }
        default:
        {
            std::lock_guard<std::mutex> logGuard( m_logMtx );
            spdlog::info( message );
        }
    }
#endif // CUL_USE_WCHAR
}

LoggerSimpleStandardOutput::~LoggerSimpleStandardOutput()
{
    log( "Destroying LoggerSimpleStandardOutput... Done." );
}