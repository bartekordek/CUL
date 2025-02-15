#include "CUL/Threading/ThreadUtil.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/Threading/MultiWorkerSystem.hpp"
#include "CUL/Threading/TaskCallback.hpp"
#include "CUL/Threading/ThreadUtilObserver.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/IMPORT_tracy.hpp"

#ifdef _MSC_VER
#include "ThreadUtilityWindows.hpp"
#endif

using namespace CUL;

thread_local std::thread::id* g_currentThreadId{ nullptr };

ThreadUtil& ThreadUtil::getInstance()
{
    static ThreadUtil s_instance;
    return s_instance;
}

ThreadUtil::ThreadUtil()
{
    m_updateThreadInfoThread = std::thread( &ThreadUtil::threadInfoWorker, this );
}

std::vector<ThreadString> ThreadUtil::getThreadNames() const
{
    ZoneScoped;
    std::vector<ThreadString> result;

    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );
    for( const auto& thread : m_threadInfo )
    {
        result.push_back( thread.second.Name );
    }
    return result;
}

bool ThreadUtil::getIsCurrentThreadNameEqualTo( const ThreadString& name ) const
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

const std::thread::id ThreadUtil::getThreadId( const ThreadString& name ) const
{
    ZoneScoped;

    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );
    const auto it = m_threadInfo.find( name );
    if( it != m_threadInfo.end() )
    {
        return it->second.ID;
    }

    return std::thread::id();
}

CULLib_API const std::thread::id& ThreadUtil::getCurrentThreadId() const
{
    if( g_currentThreadId == nullptr )
    {
        g_currentThreadId = new std::thread::id();

        *g_currentThreadId = std::this_thread::get_id();
    }

    return *g_currentThreadId;
}

ThreadString ThreadUtil::getThreadName( const std::thread::id* inThreadId ) const
{
    ZoneScoped;

    const std::thread::id* threadId{ inThreadId != nullptr ? inThreadId : &getCurrentThreadId() };

    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );

    for( const auto& threadPair : m_threadInfo )
    {
        if( threadPair.second.ID == *threadId )
        {
            return threadPair.first;
        }
    }

    return "";
}

ThreadString ThreadUtil::getThreadStatus( const std::thread::id* inThreadId ) const
{
    ZoneScoped;

    const std::thread::id* threadId{ inThreadId != nullptr ? inThreadId : &getCurrentThreadId() };

    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );

    for( const auto& threadPair : m_threadInfo )
    {
        if( threadPair.second.ID == *threadId )
        {
            return threadPair.second.Status;
        }
    }

    return "";
}
void ThreadUtil::setThreadName( const ThreadString& name, const std::thread::id* inThreadId )
{
    ZoneScoped;
    const std::thread::id& currentThreadId = getCurrentThreadId();
    const std::thread::id* threadId{ inThreadId != nullptr ? inThreadId : &currentThreadId };

    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );
    bool found{ false };

    const auto it = std::find_if( m_threadInfo.begin(), m_threadInfo.end(),
                                  [threadId]( const auto& pair )
                                  {
                                      return pair.second.ID == *threadId;
                                  } );

    ThreadMeta meta;
    meta.ID = *threadId;
    meta.Name = name;

    if( it != m_threadInfo.end() )
    {
        meta.Status = it->second.Status;
        m_threadInfo.erase( it );
    }
    else
    {

    }

    m_threadInfo[name] = meta;

#if defined( _MSC_VER )
    if( *threadId == currentThreadId )
    {
        setCurrentThreadNameWin( name );
    }
#endif
}

void ThreadUtil::setThreadStatus( const ThreadString& status, const std::thread::id* inThreadId )
{
    ZoneScoped;
    const std::thread::id* threadId{ inThreadId ? inThreadId : &getCurrentThreadId() };

    std::lock_guard<std::mutex> locker( m_tasksMtx );
    m_tasks.push_front( [this, status, threadId]() {
            setThreadStatusImpl( status, *threadId );
    } );
}

void ThreadUtil::setThreadStatusImpl( const ThreadString& status, const std::thread::id& threadId )
{
    ZoneScoped;
    std::lock_guard<std::mutex> m_threadInfoLocker( m_threadInfoMtx );

    for( auto& threadPair : m_threadInfo )
    {
        if( threadPair.second.ID == threadId )
        {
            ThreadMeta& metaCopy = threadPair.second;
            metaCopy.Status = status;
        }
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