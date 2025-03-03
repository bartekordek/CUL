#include "CUL/Task/TaskAccumulator.hpp"
#include "CUL/IMPORT_tracy.hpp"

using namespace CUL;

CTaskAccumulator::CTaskAccumulator()
{
}

void CTaskAccumulator::addTask( std::function<void( void )> inTask )
{
    ZoneScoped;
    std::lock_guard<std::mutex> locker( m_tasksMtx );
    m_tasks.push_back( inTask );
}

void CTaskAccumulator::executeOne()
{
    ZoneScoped;
    std::function<void( void )> currentTask;
    {
        std::lock_guard<std::mutex> locker( m_tasksMtx );
        if( m_tasks.empty() == false )
        {
            currentTask = *m_tasks.begin();
            m_tasks.erase( m_tasks.begin() );
        }
    }

    if( currentTask )
    {
        currentTask();
    }
}

void CTaskAccumulator::executeAll()
{
    ZoneScoped;
    std::lock_guard<std::mutex> locker( m_tasksMtx );
    for( std::function<void( void )>& currentTask : m_tasks )
    {
        currentTask();
    }
    m_tasks.clear();
}

CTaskAccumulator::~CTaskAccumulator()
{
}
