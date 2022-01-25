#include "Log/LoggerSimpleStandardOutput.hpp"
#include "IMPORT_spdlog.hpp"

#undef ERROR

using namespace CUL;
using namespace LOG;

LoggerSimpleStandardOutput::LoggerSimpleStandardOutput()
{
    log( "Iniatializing LoggerSimpleStandardOutput... Done." );
}

void LoggerSimpleStandardOutput::log(
    const String& text,
    const Severity severity )
{
    std::lock_guard<std::mutex> logGuard( m_logMtx );
    const auto& message = text.cStr();
    switch( severity )
    {
    case Severity::CRITICAL:
        spdlog::critical( message );
        break;
    case Severity::ERROR:
        spdlog::error( message );
        break;
    case Severity::WARN:
        spdlog::warn( message );
        break;
    case Severity::INFO:
        spdlog::info( message );
    }
}


LoggerSimpleStandardOutput::~LoggerSimpleStandardOutput()
{
    log( "Destroying LoggerSimpleStandardOutput... Done." );
}