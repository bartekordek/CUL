#include "CUL/Threading/ThreadWrap.hpp"

using namespace CUL;

ThreadWrapper::ThreadWrapper()
{
}

ThreadWrapper::ThreadWrapper( std::function<void( void )> threadBody ) :
    m_mainThread( std::thread( &ThreadWrapper::threadBody, this ) )
{
}

void ThreadWrapper::setBody( std::function<void( void )> threadBody )
{
    m_body = threadBody;
}

void ThreadWrapper::run()
{
    waitForCompletion();
    m_mainThread = std::thread( &ThreadWrapper::threadBody, this );
}

void ThreadWrapper::threadBody()
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