#include "CUL/Log/ILogger.hpp"
#include "Log/LoggerSimpleStandardOutput.hpp"

using ILogger = CUL::LOG::ILogger;

ILogger* ILogger::createSimpleStandardOutputLogger()
{
    return new LoggerSimpleStandardOutput();
}