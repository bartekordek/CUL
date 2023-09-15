#include "CUL/Threading/Worker.hpp"

#include "CUL/ITimer.hpp"
#include "CUL/Threading/ThreadUtil.hpp"

using namespace CUL;

Worker::Worker()
{
}

Worker::Worker( LOG::ILogger* logger ) : m_logger( logger )
{
}

void Worker::run()
{
    m_consumeThread = std::thread( &Worker::consumeThreadFunction, this );
}

void Worker::setThreadName( const String& name )
{
    m_threadName = name;
    m_updateThreadName = true;
}

void Worker::addTask( const std::function<void( void )>& task )
{
    std::lock_guard lock( m_tasksMtx );
    m_tasks.push_back( task );
}

size_t Worker::tasksLeft() const
{
    size_t result = 0;
    {
        std::lock_guard lock( m_tasksMtx );
        result = m_tasks.size();
    }
    return result;
}

void Worker::setRemoveTasksWhenConsumed( bool enable )
{
    m_removeTasksWhenConsumed = enable;
}

void Worker::consumeThreadFunction()
{
    while( m_run )
    {
        if( m_updateThreadName )
        {
            CUL::ThreadUtil::getInstance().setThreadName( m_threadName );
            m_updateThreadName = false;
        }

        if( m_removeTasksWhenConsumed )
        {
            std::function<void( void )> task;
            {
                std::lock_guard lock( m_tasksMtx );
                if( m_tasks.size() > 0 )
                {
                    task = m_tasks.front();
                    m_tasks.pop_front();
                }
                else
                {
                    continue;
                }
            }
            if( task )
            {
                task();
            }
        }
        else
        {
            std::lock_guard lock( m_tasksMtx );
            for( auto task : m_tasks )
            {
                task();
            }
        }

        ITimer::sleepMiliSeconds( (int)SleepMS );
    }
}

Worker::~Worker()
{
    while( tasksLeft() > 0 )
    {
    }

    m_run = false;
    if( m_consumeThread.joinable() )
    {
        m_consumeThread.join();
    }
}