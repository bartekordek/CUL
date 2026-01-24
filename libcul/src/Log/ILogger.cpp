#include "CUL/Log/ILogger.hpp"
#include "Log/LoggerSimpleStandardOutput.hpp"

using ILogger = CUL::LOG::ILogger;

ILogger* ILogger::s_instancePtr = nullptr;

ILogger& ILogger::getInstance()
{
    static LoggerSimpleStandardOutput s_instance;
    return s_instance;
}

ILogger::ILogger()
{
    s_instancePtr = this;
}

void ILogger::logInfo( const char* msg... )
{
    logVariable( CUL::LOG::Severity::Info, msg );
}

ILogger::~ILogger()
{
}