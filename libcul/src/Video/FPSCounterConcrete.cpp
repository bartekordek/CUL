#include "FPSCounterConcrete.hpp"

using namespace CUL;
using namespace Video;

FPSCounterConcrete::FPSCounterConcrete()
{
    this->m_samples.set_capacity( this->bufferSize );
    this->timer.reset( CUL::TimerFactory::getChronoTimer() );
}

FPSCounterConcrete::~FPSCounterConcrete()
{
    stop();
}

void FPSCounterConcrete::start()
{
    if( false == this->m_isRunning )
    {
        this->m_isRunning = true;
        this->mainThread = std::thread( &FPSCounterConcrete::counterLoop, this );
    }
}

void FPSCounterConcrete::stop()
{
    if( this->m_isRunning )
    {
        this->m_isRunning = false;
        this->mainThread.join();
    }
}

void FPSCounterConcrete::increase()
{
    ++this->framesCount;
}

const double FPSCounterConcrete::getCurrentFps() const
{
    return this->lastFrameValue * 1.0;
}

const double FPSCounterConcrete::getAverageFps() const
{
    return this->averageFps;
}

void FPSCounterConcrete::setSampleSize( unsigned short sampleSize )
{
    this->m_samples.resize( sampleSize );
}

void FPSCounterConcrete::counterLoop()
{
    while( this->m_isRunning )
    {
        this->timer->sleepSeconds( 1 );
        this->lastFrameValue.store( this->framesCount );
        this->m_samples.push_front( this->lastFrameValue );
        this->averageFps = calculateAverageFps();
        this->framesCount = 0;
    }
}

const double FPSCounterConcrete::calculateAverageFps()const
{
    if( 0 == this->m_samples.size() )
    {
        return 0.0;
    }

    double sum = 0.0;
    for( auto sampleVal: this->m_samples )
    {
        sum += sampleVal;
    }

    auto result = sum / m_samples.size();
    return result;
}