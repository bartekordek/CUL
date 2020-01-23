#pragma once

#include "CUL/Log/ILogger.hpp"
#include "CUL/STL_IMPORTS/STD_queue.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( LOG )

using LogEntry = std::pair<std::string, Severity>;

class LoggerSimpleStandardOutput:
    public ILogger
{
public:
    LoggerSimpleStandardOutput();
    ~LoggerSimpleStandardOutput();

    void log(
        const String& text,
        const Severity severity = Severity::INFO ) override;

protected:
private:
    LoggerSimpleStandardOutput(
        const LoggerSimpleStandardOutput& arg ) = delete;
    LoggerSimpleStandardOutput& operator=(
        const LoggerSimpleStandardOutput& arg ) = delete;

    std::queue<LogEntry> m_logslist;
    std::mutex m_logMtx;
};

NAMESPACE_END( LOG )
NAMESPACE_END( CUL )