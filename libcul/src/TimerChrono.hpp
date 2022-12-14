#pragma once

#include "CUL/ITimer.hpp"
#include "CUL/ITime.hpp"

#include "STD_chrono.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_atomic.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif

class TimerChrono final:
    public ITimer
{
public:
    TimerChrono( LOG::ILogger* logger );

    void start() override;
    void stop() override;
    void reset() override;
    const ITime& getElapsed() const override;

    void runEveryPeriod( std::function<void(void)> callback, unsigned uSeconds ) override;

    ~TimerChrono();

protected:
private:
    void timerLoop();
    void threadWrap( size_t index );

    unsigned getUniqueNumber();
    void removeUniqueNumber( unsigned value );
    std::set<unsigned> m_existingNumbers;

    std::chrono::high_resolution_clock clock;
    std::unique_ptr<ITime> time;
    std::chrono::high_resolution_clock::time_point startPoint;

    std::thread m_timerThread;
    std::atomic<bool> m_runLoop = false;
    unsigned m_sleepUs = 0u;
    std::function<void(void)> m_callback;

    std::mutex m_threadsMtx;
    std::map<size_t,std::thread*> m_threads;
    std::thread m_callbackThread;

    std::mutex m_threadsVectorLock;


    std::mutex m_tasksLock;
    std::vector<std::function<void( void )>> m_tasks;

    std::unique_ptr<class Worker> m_worker;

private: // Deleted
    TimerChrono( const TimerChrono& tc ) = delete;
    TimerChrono& operator=( const TimerChrono& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )