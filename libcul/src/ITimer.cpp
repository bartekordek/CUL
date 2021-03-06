#include "CUL/ITimer.hpp"
#include "TimerChrono.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"

using namespace CUL;

ITimer::ITimer()
{
}

ITimer::~ITimer()
{
}

ITimer* TimerFactory::getChronoTimer()
{
    return new TimerChrono();
}

void ITimer::sleepSeconds( const unsigned int seconds )
{
    std::this_thread::sleep_for( std::chrono::seconds( seconds ) );
}

void ITimer::sleepMiliSeconds( const unsigned int mSeconds )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( mSeconds ) );
}

void ITimer::sleepMicroSeconds( const unsigned int uSeconds )
{
    std::this_thread::sleep_for( std::chrono::microseconds( uSeconds ) );
}

void ITimer::sleepSeconds( const int seconds )
{
    std::this_thread::sleep_for( std::chrono::seconds( seconds ) );
}

void ITimer::sleepMiliSeconds( const int mSeconds )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( mSeconds ) );
}

void ITimer::sleepMicroSeconds( const int uSeconds )
{
    std::this_thread::sleep_for( std::chrono::microseconds( uSeconds ) );
}