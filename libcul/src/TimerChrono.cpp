#include "TimerChrono.hpp"
#include "TimeConcrete.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"

using namespace CUL;

TimerChrono::TimerChrono():
    time( new TimeConcrete() )
{
}

TimerChrono::~TimerChrono()
{
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