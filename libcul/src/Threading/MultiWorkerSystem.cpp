#include "CUL/Threading/MultiWorkerSystem.hpp"
#include "CUL/Threading/ThreadUtil.hpp"
#include "CUL/Threading/ITask.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/Threading/TaskCallback.hpp"

using namespace CUL;

void MultiWorkerSystem::registerTask( ITask* task )
{
    const auto prioType = task->Priority;
    std::lock_guard<std::mutex> locker( m_tasksMtxs[(size_t)prioType] );
    m_tasksArray[(size_t)prioType].push_back( task );
}

MultiWorkerSystem::MultiWorkerSystem()
{
    m_sleepMapping[EPriority::High] = 0;
    m_sleepMapping[EPriority::Medium] = 1;
    m_sleepMapping[EPriority::Low] = 2;

    CUL::ThreadUtil::getInstance().registerObserver( this );

    addWorker(EPriority::High);
}

void MultiWorkerSystem::setWorkerThreadName( int8_t id, const String& name )
{
    TaskCallback* taskPtr = new TaskCallback();
    taskPtr->Callback = [name]( int8_t ) {
        CUL::ThreadUtil::getInstance().setThreadName( name );
    };
    taskPtr->OnlyForWorkerOfId = id;
    taskPtr->Type = ITask::EType::DeleteAfterExecute;
    registerTask( taskPtr );
}

//void MultiWorkerSystem::fetchWorkerStatus()
//{
//
//}

std::vector<String> MultiWorkerSystem::getWorkersStatuses()
{
    std::lock_guard<std::mutex> locker( m_workersRunMtx );
    std::vector<String> result;
    for( const auto& thread : m_threads )
    {
        const auto id = thread.second->Thread.get_id();
        const auto status = CUL::ThreadUtil::getInstance().getThreadStatus( &id );
        result.push_back( status );
    }
    return result;

    //return m_workerStatus;
}

void MultiWorkerSystem::addWorker( EPriority priority )
{
    if( m_changeWorkers.valid() )
    {
        return;
    }

    std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
    const size_t workerId = m_threads.size();
    ThreadInfo* threadInfo = new ThreadInfo;
    threadInfo->Thread = std::thread( &MultiWorkerSystem::workerMethod, this, workerId, priority );
    threadInfo->Priority = priority;
    threadInfo->WorkerId = (int8_t)workerId;
    m_threads[threadInfo->Thread.get_id()] = threadInfo;
    // std::lock_guard<std::mutex> lockerStat( m_workerStatusMtx );
    // m_workerStatus.push_back( "Idle" );
}
void MultiWorkerSystem::removeWorker( EPriority priority )
{
    {
        std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
        ThreadInfo* foundThread{ nullptr };
        for( const auto& [it, thread] : m_threads )
        {
            if( thread->Priority == priority )
            {
                foundThread = thread;
                break;
            }
        }
        if( foundThread )
        {
            if( m_changeWorkers.valid() )
            {
                return;
            }

            m_changeWorkers = std::async(
                std::launch::async,
                [this, foundThread]()
                {
                    const std::thread::id threaId = foundThread->Thread.get_id();
                    if( foundThread->Thread.joinable() )
                    {
                        foundThread->Thread.join();
                    }
                    delete foundThread;
                    removeThreadFromWorkers( threaId );
                    m_changeWorkers = std::future<void>();
                } );

        }
    }
}

void MultiWorkerSystem::removeThreadFromWorkers( const std::thread::id& id )
{
    std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
    const auto it = m_threads.find( id );
    if( it != m_threads.end() )
    {
        m_threads.erase( id );
    }
}

MultiWorkerSystem::~MultiWorkerSystem()
{
    stopWorkers();
}


void MultiWorkerSystem::stopWorkers()
{
    std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
    m_runWorkers = false;
    for( auto& [id, currentThread] : m_threads )
    {
        if( currentThread->Thread.joinable() )
        {
            currentThread->Thread.join();
        }
        delete currentThread;
    }
    //std::lock_guard<std::mutex> lockerStat( m_workerStatusMtx );
    //m_workerStatus.pop_back();
}

void MultiWorkerSystem::workerMethod( int8_t threadId, EPriority priority )
{
    String currentThreadName = "Worker " + std::to_string( threadId );
    if( priority == EPriority::High )
    {
        currentThreadName += " [High]";
    }
    else if( priority == EPriority::Medium )
    {
        currentThreadName += " [Medium]";
    }
    else if( priority == EPriority::Low )
    {
        currentThreadName += " [Low]";
    }

    CUL::ThreadUtil::getInstance().setThreadName( currentThreadName );

    {
        std::lock_guard<std::mutex> locker( m_workersRunMtx );
        m_workersRun[threadId] = true;
    }

    while( m_runWorkers )
    {
        ITask* task = nullptr;
        {
            std::lock_guard<std::mutex> locker( m_tasksMtxs[( size_t )priority] );
            auto& tasks = m_tasksArray[(size_t)priority];
            const auto taskIt = std::find_if( tasks.begin(), tasks.end(),
                                           [priority]( const ITask* task )
                                           {


                                               return task->Priority == priority;
                                           } );

            if( taskIt != tasks.end() )
            {
                task = *taskIt;
                if( task->OnlyForWorkerOfId != -1 && task->OnlyForWorkerOfId != threadId )
                {
                }
                else
                {
                    task = *taskIt;
                    tasks.erase( taskIt );
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
                registerTask( task );
            }
        }

        std::lock_guard<std::mutex> locker( m_workersRunMtx );
        if( m_workersRun[threadId] == false )
        {
            break;
        }
    }
}

void MultiWorkerSystem::onThreadsStateUpdated( const std::vector<ThreadMeta>& ti )
{
    std::vector<String> data;

    for( const auto& info: ti )
    {
        data.push_back( info.Status );
    }

    //updateWorkerStatus( data );
}
//
//void MultiWorkerSystem::updateWorkerStatus( const std::vector<String>& in )
//{
//    std::lock_guard<std::mutex> locker( m_workersRunMtx );
//    m_workerStatus = in;
//}

int8_t MultiWorkerSystem::getCurrentWorkersCount() const
{
    int8_t currentCount = 0;
    {
        std::lock_guard<std::mutex> threadsLocker( m_threadsMtx );
        currentCount = static_cast<int8_t>( m_threads.size() );
    }
    return currentCount;
}

uint8_t MultiWorkerSystem::getTasksLeft( EPriority priority ) const
{
    uint8_t result = 0u;
    {
        std::lock_guard<std::mutex> locker( m_tasksMtxs[(size_t)priority] );
        auto& tasks = m_tasksArray[(size_t)priority];
        result = static_cast<uint8_t>( tasks.size() );
    }

    return result;
}

int8_t MultiWorkerSystem::getCurrentThreadWorkerId() const
{
    const auto currentThreadId =  CUL::ThreadUtil::getInstance().getCurrentThreadId();
    std::lock_guard<std::mutex> m_threadsMtxLocker( m_threadsMtx );
    const auto it = m_threads.find( currentThreadId );

    if( it != m_threads.end() )
    {
        ThreadInfo* ti = it->second;
        return ti->WorkerId;
    }
    return -1;
}

ThreadInfo::ThreadInfo( ThreadInfo&& arg ) noexcept
{
    Thread = std::move( arg.Thread );
    WorkerId = arg.WorkerId;
    Priority = arg.Priority;

    arg.WorkerId = -1;
    arg.Priority = EPriority::None;
}

ThreadInfo& ThreadInfo::operator=( ThreadInfo&& arg ) noexcept
{
    if( this != &arg )
    {
        Thread = std::move( arg.Thread );
        WorkerId = arg.WorkerId;
        Priority = arg.Priority;

        arg.WorkerId = -1;
        arg.Priority = EPriority::None;
    }
    return *this;
}