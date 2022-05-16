#include "CUL/Threading/ThreadWrap.hpp"

using namespace CUL;

ThreadWrapper::ThreadWrapper( std::function<void( void )> threadBody ) : m_body( threadBody )
{
    m_mainThread = std::thread( &ThreadWrapper::run, this );
}

void ThreadWrapper::run()
{
    m_body();
}

ThreadWrapper::~ThreadWrapper()
{
    waitForCompletion();
}

void ThreadWrapper::waitForCompletion()
{
    if( m_mainThread.joinable() )
    {
        m_mainThread.join();
    }
}