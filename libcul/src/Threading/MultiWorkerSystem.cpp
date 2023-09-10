#include "CUL/Threading/MultiWorkerSystem.hpp"
#include "CUL/Threading/ThreadUtils.hpp"
#include "CUL/Threading/ITask.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

using namespace CUL;

void MultiWorkerSystem::setWorkersCount( size_t count )
{
    const int8_t diff = static_cast<int8_t>( count ) - getCurrentWorkersCount();
    if( diff > 0 )
    {
        for( int8_t i = 0; i < diff; ++i )
        {
            addWorker();
        }
    }
    else if( diff < 0 )
    {
        for( int8_t i = 0; i < -diff; ++i )
        {
            removeWorker();
        }
    }
}

void MultiWorkerSystem::startTask( ITask* task )
{
    std::lock_guard<std::mutex> locker( m_tasksMtx );
    m_tasks.push_front( task );
}

MultiWorkerSystem::MultiWorkerSystem()
{

}

MultiWorkerSystem::~MultiWorkerSystem()
{
    stopWorkers();
}

void MultiWorkerSystem::stopWorkers()
{
    std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
    m_runWorkers = false;
    for( auto& currThread : m_threads )
    {
        if( currThread.joinable() )
        {
            currThread.join();
        }
    }
}

void MultiWorkerSystem::addWorker()
{
    std::thread worker( &MultiWorkerSystem::workerMethod, this );
}

void MultiWorkerSystem::removeWorker()
{
    std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
    if( m_threads.empty() == false )
    {
        if( m_threads.back().joinable())
        {
            m_threads.back().join();
            m_threads.pop_back();
        }
    }
}

void MultiWorkerSystem::workerMethod()
{
    const auto threadsCount = getCurrentWorkersCount();
    const String currentThreadName = "Worker " + std::to_string( threadsCount );

    CUL::ThreadUtils::setCurrentThreadNameStatic( currentThreadName );

    while( m_runWorkers )
    {
        ITask* task = nullptr;
        {
            std::lock_guard<std::mutex> locker( m_tasksMtx );
            if( m_tasks.empty() == false )
            {
                task = m_tasks.back();
                m_tasks.pop_back();
            }
        }
        if( task )
        {
            task->execute();
            if( task->AfterExecutionCallback )
            {
                task->AfterExecutionCallback();
            }
            if( task->DeleteAfterCompletion )
            {
                delete task;
            }
        }
        else
        {
            ITimer::sleepMiliSeconds( WorkerSleepBetweenTasksTime );
        }
    }
}

int8_t MultiWorkerSystem::getCurrentWorkersCount() const
{
    int8_t currentCount = 0;
    {
        std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
        currentCount = static_cast<int8_t>( m_threads.size() );
    }
    return currentCount;
}