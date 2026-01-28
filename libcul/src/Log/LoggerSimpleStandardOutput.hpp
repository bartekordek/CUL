#pragma once

#include "CUL/Log/ILogger.hpp"
#include "CUL/STL_IMPORTS/STD_queue.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

namespace spdlog
{
class logger;
}

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( LOG )

using LogEntry = std::pair<std::string, Severity>;

class LoggerSimpleStandardOutput final: public ILogger
{
public:
    LoggerSimpleStandardOutput();
    ~LoggerSimpleStandardOutput();

    void log( const String& text, const Severity severity = Severity::Info ) override;
    void log( const char* text, const Severity severity = Severity::Info ) override;
    void log( const wchar_t* text, const Severity severity = Severity::Info ) override;

    // TODO: Create wchar_t/std::wstring methods.
    void logVariable( Severity severity, const char* msg... ) override;
    void logInfo( const char* msg... ) override;

protected:
private:
    LoggerSimpleStandardOutput( const LoggerSimpleStandardOutput& arg ) = delete;
    LoggerSimpleStandardOutput& operator=( const LoggerSimpleStandardOutput& arg ) = delete;
    void init();

    std::shared_ptr<spdlog::logger> m_logger;
    std::queue<LogEntry> m_logslist;
    std::mutex m_logMtx;

    std::mutex m_variableMutex;
    static constexpr std::size_t s_bufferSize{ 1024 };
    char m_variableBuffer[s_bufferSize];
};

NAMESPACE_END( LOG )
NAMESPACE_END( CUL )