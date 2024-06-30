#pragma once

#include "CUL/Log/ILogger.hpp"
#include "CUL/STL_IMPORTS/STD_queue.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( LOG )

using LogEntry = std::pair<std::string, Severity>;

class LoggerSimpleStandardOutput final: public ILogger
{
public:
    LoggerSimpleStandardOutput();
    ~LoggerSimpleStandardOutput();

    void log( const String& text, const Severity severity = Severity::INFO ) override;
    void log( const char* text, const Severity severity = Severity::INFO ) override;

    void logVariable( Severity severity, const char* msg... );

protected:
private:
    LoggerSimpleStandardOutput( const LoggerSimpleStandardOutput& arg ) = delete;
    LoggerSimpleStandardOutput& operator=( const LoggerSimpleStandardOutput& arg ) = delete;

    std::queue<LogEntry> m_logslist;
    std::mutex m_logMtx;

    std::mutex m_variableMutex;
    char m_variableBuffer[512];
};

NAMESPACE_END( LOG )
NAMESPACE_END( CUL )