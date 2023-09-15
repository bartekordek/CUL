#include "CUL/Threading/ThreadUtil.hpp"

#ifdef _MSC_VER
#include "ThreadUtilityWindows.hpp"
#endif

using namespace CUL;


ThreadUtil& ThreadUtil::getInstance()
{
    static ThreadUtil s_instance;
    return s_instance;
}

ThreadUtil::ThreadUtil()
{
}

std::vector<String> ThreadUtil::getThreadNames() const
{
    std::vector<String> result;

    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );
    for( const auto& thread : m_threadInfo )
    {
        result.push_back( thread.second.Name );
    }
    return result;
}

CULLib_API bool ThreadUtil::getIsCurrentThreadNameEqualTo( const String& name ) const
{
    const auto currentThreadIdName = getThreadName();
    return name == currentThreadIdName;
}

void ThreadUtil::sleepFor( uint16_t ms )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( ms ) );
}

String ThreadUtil::getThreadName( const std::thread::id* threadId ) const
{
    const std::thread::id currentThreadId = threadId ? *threadId : std::this_thread::get_id();
    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );
    const auto it = m_threadInfo.find( currentThreadId );
    if( it == m_threadInfo.end() )
    {
        return "";
    }

    return it->second.Name;
}

String ThreadUtil::getThreadStatus( const std::thread::id* threadId ) const
{
    const std::thread::id currentThreadId = threadId ? *threadId : std::this_thread::get_id();
    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );
    const auto it = m_threadInfo.find( currentThreadId );
    if( it == m_threadInfo.end() )
    {
        return "";
    }

    return it->second.Status;
}

const std::thread::id ThreadUtil::getCurrentThreadId() const
{
    const std::thread::id currentThreadId = std::this_thread::get_id();
    return currentThreadId;
}

void ThreadUtil::setThreadName( const String& name, const std::thread::id* threadId )
{
    const std::thread::id currentThreadId = threadId ? *threadId : std::this_thread::get_id();
    {
        std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );

        const auto it = m_threadInfo.find( currentThreadId );
        if( it != m_threadInfo.end() )
        {
            it->second.Name = name;
        }
        else
        {
            ThreadInfo ti;
            ti.Name = name;
            m_threadInfo[currentThreadId] = ti;
        }
    }

#ifdef _MSC_VER
    setCurrentThreadNameWin( name );
#endif
}

void ThreadUtil::setThreadStatus( const String& status, const std::thread::id* threadId )
{
    const std::thread::id currentThreadId = threadId ? *threadId : std::this_thread::get_id();
    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );
    const auto it = m_threadInfo.find( currentThreadId );
    if( it != m_threadInfo.end() )
    {
        it->second.Status = status;
    }
    else
    {
        ThreadInfo ti;
        ti.Status = status;
        m_threadInfo[currentThreadId] = ti;
    }
}


ThreadUtil::~ThreadUtil()
{
}