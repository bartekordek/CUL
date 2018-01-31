#include "TimerChrono.hpp"
#include "TimeConcrete.hpp"
#include <chrono>
#include <thread>
#include <memory>
using namespace CUL;

TimerChrono::TimerChrono( const bool run )
{
    this->time.reset( new TimeConcrete() );
    if( run )
    {
        this->reset();
    }
}

TimerChrono::~TimerChrono()
{
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