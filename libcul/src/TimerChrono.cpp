#include "TimerChrono.hpp"
#include "TimeConcrete.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"

using namespace CUL;

TimerChrono::TimerChrono( const bool run )
{
    time.reset( new TimeConcrete() );
    if( run )
    {
        reset();
    }
}

TimerChrono::TimerChrono( const TimerChrono& tc ):
    clock( tc.clock ),
    time(
    new TimeConcrete(
    *static_cast<TimeConcrete*>( tc.time.get() ) ) )
{

}

TimerChrono::~TimerChrono()
{
}

TimerChrono& TimerChrono::operator=( const TimerChrono& rhv )
{
    if( &rhv != this )
    {
        clock = rhv.clock;
        time.reset(
            new TimeConcrete(
            *static_cast<TimeConcrete*>( rhv.time.get() ) ) );
        startPoint = rhv.startPoint;
    }
    return *this;
}

void TimerChrono::start()
{
    reset();
}

void TimerChrono::stop()
{
}

void TimerChrono::reset()
{
    startPoint = clock.now();
}

const ITime& TimerChrono::getElapsed() const
{
    auto difference = clock.now() - startPoint;
    auto us =
        std::chrono::duration_cast<std::chrono::microseconds>(
        difference ).count();
    auto d_us = static_cast<double>( us );
    time->setTimeUs( d_us );
    return *time;
}