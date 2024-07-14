#include "CUL/Log/ILogger.hpp"
#include "Log/LoggerSimpleStandardOutput.hpp"

using ILogger = CUL::LOG::ILogger;

ILogger* ILogger::s_instancePtr = nullptr;

ILogger::ILogger()
{
    s_instancePtr = this;
}

ILogger& ILogger::getInstance()
{
    static LoggerSimpleStandardOutput s_instance;
    return s_instance;
}

ILogger::~ILogger()
{
}