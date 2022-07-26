#include "CUL/ITimer.hpp"
#include "TimerChrono.hpp"

#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;

ITimer::ITimer()
{
}

ITimer::~ITimer()
{
}

ITimer* TimerFactory::getChronoTimer()
{
    auto ptr = new TimerChrono();
    std::cout << "TimerChrono size: " << sizeof( TimerChrono ) << "\n";
    return ptr;
}

void ITimer::sleepSeconds( unsigned int seconds )
{
    std::this_thread::sleep_for( std::chrono::seconds( seconds ) );
}

void ITimer::sleepMiliSeconds( unsigned int mSeconds )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( mSeconds ) );
}

void ITimer::sleepMicroSeconds( unsigned int uSeconds )
{
    std::this_thread::sleep_for( std::chrono::microseconds( uSeconds ) );
}

void ITimer::sleepSeconds( int seconds )
{
    std::this_thread::sleep_for( std::chrono::seconds( seconds ) );
}

void ITimer::sleepMiliSeconds( int mSeconds )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( mSeconds ) );
}

void ITimer::sleepMicroSeconds( int uSeconds )
{
    std::this_thread::sleep_for( std::chrono::microseconds( uSeconds ) );
}

void ITimer::sleepSeconds( float seconds )
{
    std::this_thread::sleep_for( std::chrono::seconds( (int)seconds ) );
}

void ITimer::sleepMiliSeconds( float mSeconds )
{
    std::this_thread::sleep_for( std::chrono::milliseconds( (int)mSeconds ) );
}

void ITimer::sleepMicroSeconds( float uSeconds )
{
    std::this_thread::sleep_for( std::chrono::microseconds( (int)uSeconds ) );
}