#include "CUL/Log/ILogger.hpp"
#include "Log/LoggerSimpleStandardOutput.hpp"

using ILogger = CUL::LOG::ILogger;

ILogger* ILogger::s_instance = nullptr;

ILogger* ILogger::createSimpleStandardOutputLogger()
{
    s_instance = new LoggerSimpleStandardOutput();
    return s_instance;
}

ILogger::ILogger()
{
    s_instance = this;
}

ILogger* ILogger::getInstance()
{
    return s_instance;
}

ILogger::~ILogger()
{
}