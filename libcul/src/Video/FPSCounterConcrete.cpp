#include "FPSCounterConcrete.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;
using namespace Video;

FPSCounterConcrete::FPSCounterConcrete()
{
    m_samples.set_capacity( bufferSize );
    m_timer.reset( CUL::TimerFactory::getChronoTimer() );
}

FPSCounterConcrete::~FPSCounterConcrete()
{
    if( m_isRunning )
    {
        stop();
    }
}

void FPSCounterConcrete::start()
{
    if( false == m_isRunning )
    {
        m_isRunning = true;
        m_mainThread = std::thread( &FPSCounterConcrete::counterLoop, this );
    }
}

void FPSCounterConcrete::stop()
{
    if( m_isRunning )
    {
        m_isRunning = false;
        m_mainThread.join();
    }
}

void FPSCounterConcrete::increase()
{
    ++m_framesCount;
}

const double FPSCounterConcrete::getCurrentFps() const
{
    return m_lastFrameValue * 1.0;
}

const double FPSCounterConcrete::getAverageFps() const
{
    return m_averageFps;
}

void FPSCounterConcrete::setSampleSize( unsigned short sampleSize )
{
    m_samples.resize( sampleSize );
}

void FPSCounterConcrete::setMeasurePeriod( const unsigned periodMs )
{
    m_sleepTimeMs = periodMs;
}

void FPSCounterConcrete::counterLoop()
{
    while( m_isRunning )
    {
        m_timer->sleepMiliSeconds( m_sleepTimeMs );
        m_lastFrameValue.store( m_framesCount );
        m_samples.push_front( m_lastFrameValue );
        m_averageFps = calculateAverageFps();
        m_framesCount = 0;
    }
}

const double FPSCounterConcrete::calculateAverageFps()const
{
    if( 0 == m_samples.size() )
    {
        return 0.0;
    }

    double sum = 0.0;
    for( auto sampleVal: m_samples )
    {
        sum += sampleVal;
    }

    auto result = sum / m_samples.size();
    return normalizeToSleepTime( result );
}

const double FPSCounterConcrete::normalizeToSleepTime( const double fpsCount ) const
{
    return fpsCount * 1000.0 / m_sleepTimeMs;
}