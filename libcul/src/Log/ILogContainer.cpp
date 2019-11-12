#include "CUL/Log/ILogContainer.hpp"
#include "Log/LoggerSimpleStandardOutput.hpp"

using namespace CUL;
using namespace LOG;
using namespace LOG_CONTAINER;

static ILogger* s_instance = nullptr;

ILogger* CUL::LOG::LOG_CONTAINER::getLogger()
{
    if( nullptr == s_instance )
    {
        s_instance = new LoggerSimpleStandardOutput();
    }
    return s_instance;
}

void CUL::LOG::LOG_CONTAINER::destroyLogger()
{
    delete s_instance;
    s_instance = nullptr;
}