#include "CUL/Threading/MultiWorkerSystem.hpp"
#include "CUL/Threading/ThreadUtil.hpp"
#include "CUL/Threading/ITask.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/Threading/TaskCallback.hpp"

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

void MultiWorkerSystem::setWorkerThreadName( int8_t id, const String& name )
{
    TaskCallback* taskPtr = new TaskCallback();
    taskPtr->Callback = [this, name]( int8_t ) {
        CUL::ThreadUtil::getInstance().setThreadName( name );
    };
    taskPtr->OnlyForWorkerOfId = id;
    taskPtr->Type = ITask::EType::DeleteAfterExecute;
    startTask( taskPtr );
}

std::vector<String> MultiWorkerSystem::getWorkersStatuses()
{
    std::vector<String> result;

    {
        std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
        for( const auto& thread : m_threads )
        {
            const auto id = thread.get_id();
            const auto status = CUL::ThreadUtil::getInstance().getThreadStatus( &id );
            result.push_back( status );
        }
    }

    return result;
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
    std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
    m_threads.push_back( std::move( std::thread( &MultiWorkerSystem::workerMethod, this, m_threads.size() ) ) );
}

void MultiWorkerSystem::removeWorker()
{
    std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
    if( m_threads.empty() == false )
    {
        {
            std::lock_guard<std::mutex> locker( m_workersRunMtx );
            const auto lastWorkerId = static_cast<int8_t>(m_threads.size() - 1);
            m_workersRun[lastWorkerId] = false;
        }

        if( m_threads.back().joinable())
        {
            m_threads.back().join();
            m_threads.pop_back();
        }
    }
}

void MultiWorkerSystem::workerMethod( int8_t threadId )
{
    const String currentThreadName = "Worker " + std::to_string( threadId );

    CUL::ThreadUtil::getInstance().setThreadName( currentThreadName );

    {
        std::lock_guard<std::mutex> locker( m_workersRunMtx );
        m_workersRun[threadId] = true;
    }

    {
        std::lock_guard<std::mutex> m_threadToWorkerIdMappingMtxLocker( m_threadToWorkerIdMappingMtx );
        m_threadToWorkerIdMapping[CUL::ThreadUtil::getInstance().getCurrentThreadId()] = threadId;
    }

    while( m_runWorkers )
    {
        ITask* task = nullptr;
        {
            std::lock_guard<std::mutex> locker( m_tasksMtx );
            if( m_tasks.empty() == false )
            {
                task = m_tasks.back();
                if( task->OnlyForWorkerOfId != -1 && task->OnlyForWorkerOfId != threadId )
                {
                    task = nullptr;
                }
                else
                {
                    m_tasks.pop_back();
                }
            }
        }
        if( task )
        {
            task->execute( threadId );

            if( task->AfterExecutionCallback )
            {
                task->AfterExecutionCallback( threadId );
            }

            if( task->Type == ITask::EType::DeleteAfterExecute )
            {
                delete task;
            }
            else if( task->Type == ITask::EType::Loop )
            {
                task->resetStatus();
                startTask( task );
            }
            ITimer::sleepMiliSeconds( WorkerSleepBetweenTasksTimeMs );
        }
        else
        {
            ITimer::sleepMiliSeconds( WorkerSleepWhenNoTaskTimeMs );
        }


        std::lock_guard<std::mutex> locker( m_workersRunMtx );
        if( m_workersRun[threadId] == false )
        {
            break;
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

uint8_t MultiWorkerSystem::getTasksLeft() const
{
    uint8_t result = 0u;
    {
        std::lock_guard<std::mutex> locker( m_tasksMtx );
        result = static_cast<uint8_t>( m_tasks.size() );
    }

    return result;
}

int8_t MultiWorkerSystem::getCurrentThreadWorkerId() const
{
    std::lock_guard<std::mutex> m_threadToWorkerIdMappingMtxLocker( m_threadToWorkerIdMappingMtx );
    const auto it = m_threadToWorkerIdMapping.find( CUL::ThreadUtil::getInstance().getCurrentThreadId() );
    if( it != m_threadToWorkerIdMapping.end() )
    {
        return it->second;
    }
    return -1;
}