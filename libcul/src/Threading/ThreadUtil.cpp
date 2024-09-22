#include "CUL/Threading/ThreadUtil.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/Threading/MultiWorkerSystem.hpp"
#include "CUL/Threading/TaskCallback.hpp"
#include "CUL/Threading/ThreadUtilObserver.hpp"

#include "CUL/IMPORT_tracy.hpp"

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
    m_updateThreadInfoThread = std::thread( &ThreadUtil::threadInfoWorker, this );
}

std::vector<String> ThreadUtil::getThreadNames() const
{
    ZoneScoped;
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

void ThreadUtil::registerObserver( CThreadUtilObserver* observer )
{
    std::lock_guard<std::mutex> locker(m_observersMtx);
    m_observers.insert( observer );
}

String ThreadUtil::getThreadName( const std::thread::id* threadId ) const
{
    ZoneScoped;
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
    ZoneScoped;
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
    ZoneScoped;
    const std::thread::id currentThreadId = std::this_thread::get_id();
    return currentThreadId;
}

void ThreadUtil::setThreadName( const String& name, const std::thread::id* threadId )
{
    ZoneScoped;
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
            ThreadMeta ti;
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
    ZoneScoped;
    const std::thread::id currentThreadId = threadId ? *threadId : std::this_thread::get_id();

    std::lock_guard<std::mutex> locker( m_tasksMtx );
    m_tasks.push_front( [this, status, currentThreadId]() {
        setThreadStatusImpl( status, currentThreadId );
    } );
}

void ThreadUtil::setThreadStatusImpl( const String& status, const std::thread::id& threadId )
{
    ZoneScoped;
    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );
    const auto it = m_threadInfo.find( threadId );
    if( it != m_threadInfo.end() )
    {
        it->second.Status = status;
    }
    else
    {
        ThreadMeta ti;
        ti.Status = status;
        m_threadInfo[threadId] = ti;
    }
}

void ThreadUtil::threadInfoWorker()
{
    setThreadName("ThreadUtil::threadInfoWorker");
    while( m_runThreadWorker )
    {
        ZoneScoped;
        std::this_thread::sleep_for( std::chrono::microseconds( 2 ) );

        std::lock_guard<std::mutex> locker( m_tasksMtx );
        while( m_tasks.empty() == false )
        {
            ZoneScoped;
            std::function<void( void )> task = m_tasks.back();
            task();
            m_tasks.pop_back();
        }
    }
}

void ThreadUtil::notifyObservers()
{
    std::vector<ThreadMeta> data;
    {
        std::lock_guard<std::mutex> locker( m_threadInfoMtx );
        for( const auto& ti : m_threadInfo )
        {
            data.push_back(ti.second);
        }
    }

    std::lock_guard<std::mutex> locker( m_observersMtx );
    for( const auto& observer: m_observers )
    {
        observer->onThreadsStateUpdated( data );
    }
}

ThreadUtil::~ThreadUtil()
{
    m_runThreadWorker = false;
    if( m_updateThreadInfoThread.joinable() )
    {
        m_updateThreadInfoThread.join();
    }
}