#include "TimerChrono.hpp"
#include "TimeConcrete.hpp"
#include "Thread.hpp"

using namespace CUL;

TimerChrono::TimerChrono( const bool run )
{
    this->time.reset( new TimeConcrete() );
    if( run )
    {
        this->reset();
    }
}

TimerChrono::TimerChrono( const TimerChrono& tc ):
    clock( tc.clock ),
    time( new TimeConcrete( *static_cast<TimeConcrete*>( tc.time.get() ) ) )
{

}

TimerChrono::~TimerChrono()
{
}

TimerChrono& TimerChrono::operator=( const TimerChrono& rhv )
{
    if( &rhv != this )
    {
        this->clock = rhv.clock;
        this->time.reset( new TimeConcrete( *static_cast<TimeConcrete*>( rhv.time.get() ) ) );
        this->startPoint = rhv.startPoint;
    }
    return *this;
}

void TimerChrono::start()
{
    this->reset();
}

void TimerChrono::stop()
{
}

void TimerChrono::reset()
{
    this->startPoint = this->clock.now();
}

const ITime& TimerChrono::getElapsed() const
{
    auto difference = this->clock.now() - startPoint;
    auto us = std::chrono::duration_cast<std::chrono::microseconds>( difference ).count();
    auto d_us = static_cast<double>( us );
    this->time->setTimeUs( d_us );
    return *this->time;
}