#include "TimerChrono.hpp"
#include "CUL/Threading/Worker.hpp"
#include "CUL/Log/ILogger.hpp"

#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"

using namespace CUL;

TimerChrono::TimerChrono( LOG::ILogger* logger ):
    ITimer( logger ), time( new Time() )
{
    const bool logMe = false;

    if( logMe )
    {
        void* add = this;
        std::stringstream stream;
        stream << std::hex << add;
        std::string result( stream.str() );
        logger->log( "TimerChrono()" + result );
    }
}

void TimerChrono::start()
{
    reset();
}

void TimerChrono::stop()
{
    m_started = false;
    m_runLoop = false;
}

void TimerChrono::reset()
{
    startPoint = clock.now();
    m_started = true;
}

const Time& TimerChrono::getElapsed() const
{
    const auto difference = clock.now() - startPoint;
    const auto currentCount = std::chrono::duration_cast<std::chrono::nanoseconds>( difference ).count();
    const std::int64_t ns = static_cast<std::int64_t>( currentCount );

    const auto d_ns = static_cast<double>( ns );
    time->setTimeNs( d_ns );
    return *time;
}


std::int64_t TimerChrono::getElapsedNs() const
{
    const auto difference = clock.now() - startPoint;
    const std::int64_t ns =  std::chrono::duration_cast<std::chrono::nanoseconds>( difference ).count();
    return ns;
}


void TimerChrono::runEveryPeriod( std::function<void(void)> callback, unsigned uSeconds )
{
    if( m_timerThread.joinable() )
    {
        m_timerThread.join();
    }

    m_sleepUs = uSeconds;
    m_callback = callback;

    m_worker.reset( new Worker( getLogger() ) );

    m_runLoop = true;
    m_timerThread = std::thread( &TimerChrono::timerLoop, this );
}

void TimerChrono::timerLoop()
{
    m_worker->run();
    while( m_runLoop )
    {
        ITimer::sleepMicroSeconds( m_sleepUs );

        if( m_callback )
        {
            m_callback();
        }
    }
}

TimerChrono::~TimerChrono()
{
    m_runLoop = false;
    m_started = false;

    if( m_timerThread.joinable() )
    {
        m_timerThread.join();
    }

    while( m_worker && m_worker->tasksLeft() )
    {

    }

    const bool logMe = false;

    if( logMe )
    {
        void* add = this;
        std::stringstream stream;
        stream << std::hex << add;
        std::string result( stream.str() );
        LOG::ILogger* log = getLogger();
        log->log( "~TimerChrono()" + result );
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

void TimerChrono::removeUniqueNumber( std::size_t value )
{
    std::lock_guard<std::mutex> lock( m_threadsVectorLock );
    auto it = m_existingNumbers.find( value );
    if( it != m_existingNumbers.end() )
    {
        m_existingNumbers.erase( it );
    }
}

bool TimerChrono::getIsStarted() const
{
    return m_started;
}
