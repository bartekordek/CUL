#include "FPSCounterConcrete.hpp"

using namespace CUL;
using namespace Video;

FPSCounterConcrete::FPSCounterConcrete()
{
    this->samples.set_capacity( this->bufferSize );
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

void FPSCounterConcrete::counterLoop()
{
    while( this->m_isRunning )
    {
        this->timer->sleepSeconds( 1 );
        this->lastFrameValue.store( this->framesCount );
        this->samples.push_front( this->lastFrameValue );
        this->averageFps = calculateAverageFps();
        this->framesCount = 0;
    }
}

const double FPSCounterConcrete::calculateAverageFps()const
{
    if( 0 == this->samples.size() )
    {
        return 0.0;
    }
    auto sampleSizeRealVal = static_cast<unsigned int>( this->samples.size() );
    double sampleSizeReal = this->sampleSize < sampleSizeRealVal ? this->sampleSize : sampleSizeRealVal;

    double sum = 0.0;
    for( unsigned int i = 0; i < sampleSizeReal; ++i )
    {
        sum += this->samples[i];
    }

    auto result = sum / sampleSizeReal;
    return result;
}