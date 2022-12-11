#include "TimerChrono.hpp"
#include "CUL/TimeConcrete.hpp"
#include "CUL/Log/ILogger.hpp"

#include "CUL/STL_IMPORTS/STD_thread.hpp"

using namespace CUL;

TimerChrono::TimerChrono( LOG::ILogger* logger ):
    ITimer( logger ), time( new TimeConcrete() )
{
    void* add = this;
    std::stringstream stream;
    stream << std::hex << add;
    std::string result( stream.str() );
    logger->log( "TimerChrono()" + result );
}

void TimerChrono::start()
{
    reset();
}

void TimerChrono::stop()
{
    //TODO
}

void TimerChrono::reset()
{
    startPoint = clock.now();
}

const ITime& TimerChrono::getElapsed() const
{
    const auto difference = clock.now() - startPoint;
    auto us =
        std::chrono::duration_cast<std::chrono::microseconds>(
        difference ).count();
    const auto d_us = static_cast<double>( us );
    time->setTimeUs( d_us );
    return *time;
}

void TimerChrono::runEveryPeriod( std::function<void(void)> callback, unsigned uSeconds )
{
    if( m_timerThread.joinable() )
    {
        m_timerThread.join();
    }

    m_sleepUs = uSeconds;
    m_callback = callback;

    m_runLoop = true;
    m_timerThread = std::thread( &TimerChrono::timerLoop, this );
}

void TimerChrono::timerLoop()
{
    while( m_runLoop )
    {
        ITimer::sleepMicroSeconds( m_sleepUs );

        unsigned id = getUniqueNumber();
        std::thread* thread = new std::thread( &TimerChrono::threadWrap, this, id );
        m_threads[id] = thread;

        joinFinishedThreads();
    }
}

void TimerChrono::threadWrap( size_t index )
{
    getLogger()->log( "threadWrap[" + CUL::String( (int) index ) + "][BEGIN]" );
    if( m_callback )
    {
        m_callback();
    }

    {
        std::lock_guard<std::mutex> lock( m_threadsVectorLock );
        m_vectorsToRemove.push_back( index );
    }

    getLogger()->log( "threadWrap[" + CUL::String( (int) index ) + "][END]" );
}

TimerChrono::~TimerChrono()
{
    m_runLoop = false;

    joinFinishedThreads( true );

    if( m_timerThread.joinable() )
    {
        m_timerThread.join();
    }


    void* add = this;
    std::stringstream stream;
    stream << std::hex << add;
    std::string result( stream.str() );
    LOG::ILogger* log = getLogger();
    log->log( "~TimerChrono()" + result );
}

void TimerChrono::joinFinishedThreads( bool all )
{
    while( true )
    {
        std::lock_guard<std::mutex> lock( m_threadsVectorLock );
        if( all )
        {
            if( m_vectorsToRemove.size() == 0 && m_threads.size() == 0 )
            {
                break;
            }
        }
        else
        {
            if( m_vectorsToRemove.size() == 0 )
            {
                break;
            }
        }

        if( m_vectorsToRemove.size() > 0 )
        {
            size_t index = m_vectorsToRemove[0];
            getLogger()->log( "Kill: " + CUL::String((int)index) );
            m_vectorsToRemove.erase( m_vectorsToRemove.begin() );
            if( m_threads[index]->joinable() )
            {
                m_threads[index]->join();
                getLogger()->log( "Kill [join]: " + CUL::String( (int) index ) );
            }
            m_threads.erase( index );
        }
    }

    const size_t size = m_threads.size();

    if( size > 0 )
    {
        for( size_t i = size - 1; i > 0; --i )
        {
            std::thread& thread = *m_threads[i];
            if( thread.joinable() )
            {
                thread.join();
                m_threads.erase( i );
            }
        }
    }
}

unsigned TimerChrono::getUniqueNumber()
{
    unsigned result = 0;

    std::lock_guard<std::mutex> lock( m_threadsVectorLock );
    if( m_existingNumbers.empty() )
    {
        m_existingNumbers.insert( 0 );
        return result;
    }

    do
    {
        auto it = m_existingNumbers.find( result );
        if( it == m_existingNumbers.end() )
        {
            m_existingNumbers.insert( result );
            return result;
        }
        ++result;
    }
    while( true );
}

void TimerChrono::removeUniqueNumber( unsigned value )
{
    std::lock_guard<std::mutex> lock( m_threadsVectorLock );
    auto it = m_existingNumbers.find( value );
    if( it != m_existingNumbers.end() )
    {
        m_existingNumbers.erase( it );
    }
}