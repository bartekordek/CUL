#include "CUL/Hardware/DiskInfo.hpp"
#include "CUL/IMPORT_windows.hpp"
#include "CUL/Log/ILogger.hpp"
#include "Hardware/DiskInfoWindows.hpp"
#include "Hardware/DiskInfoDummy.hpp"
#include <CUL/STL_IMPORTS/STD_algorithm.hpp>
#include <CUL/STL_IMPORTS/STD_mutex.hpp>

#undef max



namespace CUL
{
CDiskInfo& CDiskInfo::getInstance()
{
#if defined( CUL_WINDOWS )
    static CDiskInfoWindows s_instance;
#else
    static CDiskInfoDummy s_instance;
#endif // #if defined(CUL_WINDOWS)

    return s_instance;
}

void CDiskInfo::setPoolIntervalMs( std::uint32_t inIntervalMs )
{
    m_poolIntervalMs = inIntervalMs;
}

CDiskInfo::CDiskInfo()
{
}

std::once_flag g_onceFlag;

void CDiskInfo::start( bool withDebugInfo )
{
    std::call_once( g_onceFlag, &CDiskInfo::initialize, this, withDebugInfo );

    m_run = true;
    m_mainThread.run();
    if( withDebugInfo )
    {
        m_debugInfoThread.run();
    }
}

void CDiskInfo::initialize( bool withDebugInfo )
{
    m_mainThread.setBody(
        [this]()
        {
            mainLoop();
        } );

    if( withDebugInfo )
    {
        m_debugInfoThread.setBody(
            [this]()
            {
                debugLoop();
            } );
    }
}

bool CDiskInfo::isMainLoopRunning() const
{
    return m_run;
}

std::uint32_t CDiskInfo::getPoolIntervalMs() const
{
    return m_poolIntervalMs;
}

void CDiskInfo::getInfo()
{
}

CDiskInfo::~CDiskInfo()
{
    m_run = false;
    m_mainThread.waitForCompletion();
}
}  // namespace CUL
