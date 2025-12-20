#pragma once

#include "CUL/Threading/ThreadMeta.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_optional.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_deque.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_atomic.hpp"
#include "CUL/STL_IMPORTS/STD_unordered_set.hpp"

NAMESPACE_BEGIN( CUL )

#undef Status

class CThreadUtilObserver;

using ThreadString = std::string;

class ThreadUtil final
{
public:
    CULLib_API ThreadUtil();

    CULLib_API static ThreadUtil& getInstance();

    CULLib_API void setThreadName( const ThreadString& status, const std::thread::id* inThreadId = nullptr );
    CULLib_API void setThreadStatusArgs( const std::thread::id* inThreadId, const char* msg... );
    CULLib_API void setThreadStatusArgs( const char* msg... );
    CULLib_API void setThreadStatus( const ThreadString& status, const std::thread::id* inThreadId = nullptr );
    //virtual void logVariable( Severity severity, const char* msg... ) = 0;
    CULLib_API ThreadString getThreadName( const std::thread::id* threadId = nullptr ) const;
    CULLib_API ThreadString getThreadStatus( const std::thread::id* threadId = nullptr ) const;
    CULLib_API std::vector<ThreadString> getThreadNames() const;
    CULLib_API bool getIsCurrentThreadNameEqualTo( const ThreadString& name ) const;
    CULLib_API void sleepFor( uint16_t ms );
    CULLib_API void registerObserver( CThreadUtilObserver* observer );
    CULLib_API const std::thread::id getThreadId(const std::string& name) const;
    CULLib_API const std::thread::id& getCurrentThreadId() const; 
    CULLib_API ~ThreadUtil();

    ThreadUtil& operator=( const ThreadUtil& rhv ) = delete;
    ThreadUtil& operator=( ThreadUtil&& rhv ) = delete;
    ThreadUtil( const ThreadUtil& arg ) = delete;
    ThreadUtil( ThreadUtil&& arg ) = delete;

protected:
private:
    void setThreadStatusImpl( const ThreadString& status, const std::thread::id& threadId );
    void threadInfoWorker();
    void notifyObservers();
    std::atomic_bool m_runThreadWorker{ true };

    std::unordered_map<std::string, ThreadMeta> m_threadInfo;
    mutable std::mutex m_threadInfoMtx;
    std::thread m_updateThreadInfoThread;

    std::deque<std::function<void(void)>> m_tasks;
    std::mutex m_tasksMtx;

    std::unordered_set<CThreadUtilObserver*> m_observers;
    std::mutex m_observersMtx;
};
NAMESPACE_END( CUL )