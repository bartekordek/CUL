#include "CUL/Threading/MultiWorkerSystem.hpp"
#include "CUL/Threading/ThreadUtil.hpp"
#include "CUL/Threading/ITask.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/Proifling/Profiler.hpp"
#include "CUL/Threading/TaskCallback.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"

#if 0  // DEBUG_THIS_FILE
    #define DEBUG_THIS_FILE 1
    #if defined( _MSC_VER )
        #pragma optimize( "", off )
    #else
        #pragma clang optimize off
    #endif
#endif

using namespace CUL;

std::array<std::uint64_t, static_cast<std::size_t>( EPriority::COUNT )> g_maxQueuedTasks;

void MultiWorkerSystem::registerTask( ITask* task )
{
    ProfilerScope( "MultiWorkerSystem::registerTask" );

    const auto prioType = task->Priority;
    while( true )
    {
        std::lock_guard<std::mutex> locker( m_tasksMtxs[(size_t)prioType] );
        if( getQueuedCount( prioType ) < getMaxTasksCount( prioType ) )
        {
            m_tasksArray[(size_t)prioType].push_back( task );
            return;
        }
    }
}

MultiWorkerSystem::MultiWorkerSystem()
{
    g_maxQueuedTasks[static_cast<std::size_t>( EPriority::Low )] = 4096u;
    g_maxQueuedTasks[static_cast<std::size_t>( EPriority::Medium )] = std::pow( 2u, 14u );
    g_maxQueuedTasks[static_cast<std::size_t>( EPriority::High )] = 4096u;

    m_sleepMapping[EPriority::High] = 0;
    m_sleepMapping[EPriority::Medium] = 1;
    m_sleepMapping[EPriority::Low] = 2;

    CUL::ThreadUtil::getInstance().registerObserver( this );

    addWorker( EPriority::High );
    addWorker( EPriority::High );
    addWorker( EPriority::Low );
}

void MultiWorkerSystem::setWorkerThreadName( int8_t id, const String& name )
{
    ProfilerScope( "MultiWorkerSystem::setWorkerThreadName" );

    TaskCallback* taskPtr = new TaskCallback();
    taskPtr->Callback = [name]( int8_t )
    {
        CUL::ThreadUtil::getInstance().setThreadName( name.getUtfChar() );
    };
    taskPtr->OnlyForWorkerOfId = id;
    taskPtr->Type = ITask::EType::DeleteAfterExecute;
    registerTask( taskPtr );
}

std::vector<String> MultiWorkerSystem::getWorkersStatuses()
{
    ProfilerScope( "MultiWorkerSystem::getWorkersStatuses" );

    std::lock_guard<std::mutex> locker( m_workersRunMtx );
    std::vector<String> result;
    for( const auto& thread : m_threads )
    {
        const auto id = thread.second->Thread.get_id();
        const auto status = CUL::ThreadUtil::getInstance().getThreadStatus( &id );
        result.push_back( status );
    }
    return result;
}

std::uint64_t MultiWorkerSystem::getQueuedCount( EPriority inPriority ) const
{
    ProfilerScope( "MultiWorkerSystem::getQueuedCount" );

    std::lock_guard<std::mutex> locker( m_workersRunMtx );
    return static_cast<std::uint64_t>( m_tasksArray[(size_t)inPriority].size() );
}

std::uint64_t MultiWorkerSystem::getMaxTasksCount( EPriority inPriority ) const
{
    return g_maxQueuedTasks[static_cast<std::size_t>( inPriority )];
}

void MultiWorkerSystem::setMaxTasksCount( EPriority inPriority, std::uint64_t inCount )
{
    g_maxQueuedTasks[static_cast<std::size_t>( inPriority )] = inCount;
}

void MultiWorkerSystem::addWorker( EPriority priority )
{
    ProfilerScope( "MultiWorkerSystem::addWorker" );

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
}

void MultiWorkerSystem::removeWorker( EPriority priority )
{
    ProfilerScope( "MultiWorkerSystem::removeWorker" );

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

            m_changeWorkers = std::async( std::launch::async,
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
    ProfilerScope( "MultiWorkerSystem::removeThreadFromWorkers" );

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
    // std::lock_guard<std::mutex> lockerStat( m_workerStatusMtx );
    // m_workerStatus.pop_back();
}

void MultiWorkerSystem::workerMethod( int8_t threadId, EPriority priority )
{
    ProfilerScope( "MultiWorkerSystem::workerMethod" );

    const char* workerName = EPriorityToChar( priority );

    char pathStr[512];
    sprintf( pathStr, "Worker %d [%s]", threadId, workerName );
    const String currentThreadName = pathStr;

    CUL::ThreadUtil::getInstance().setThreadName( currentThreadName.getUtfChar() );

    {
        std::lock_guard<std::mutex> locker( m_workersRunMtx );
        m_workersRun[threadId] = true;
    }

    while( m_runWorkers )
    {
        ITask* task = nullptr;
        {
            std::lock_guard<std::mutex> locker( m_tasksMtxs[(size_t)priority] );
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

    for( const auto& info : ti )
    {
        data.push_back( info.Status );
    }

    // updateWorkerStatus( data );
}
//
// void MultiWorkerSystem::updateWorkerStatus( const std::vector<String>& in )
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

std::uint64_t MultiWorkerSystem::getTasksLeft( EPriority priority ) const
{
    ProfilerScope( "MultiWorkerSystem::getTasksLeft" );

    std::uint64_t result = 0u;
    {
        std::lock_guard<std::mutex> locker( m_tasksMtxs[(size_t)priority] );
        auto& tasks = m_tasksArray[(size_t)priority];
        result = static_cast<std::uint64_t>( tasks.size() );
    }

    return result;
}

int8_t MultiWorkerSystem::getCurrentThreadWorkerId() const
{
    const auto currentThreadId = CUL::ThreadUtil::getInstance().getCurrentThreadId();
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

#if defined( DEBUG_THIS_FILE )
    #ifdef _MSC_VER
        #pragma optimize( "", on )
    #else
        #pragma clang optimize on
    #endif
#endif  // #if defined(DEBUG_THIS_FILE)