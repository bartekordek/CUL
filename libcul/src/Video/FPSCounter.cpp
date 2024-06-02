#include "CUL/Video/FPSCounter.hpp"
#include "TimerChrono.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;
using namespace Video;

FPSCounter::FPSCounter( CUL::LOG::ILogger* logger )
{
    m_timer = std::make_unique< TimerChrono>( logger );
    m_samples.setCapacity( m_bufferSize );
}

void FPSCounter::start()
{
    if( false == m_isRunning )
    {
        m_isRunning = true;
        m_timer->start();
        m_mainThread = std::thread( &FPSCounter::counterLoop, this );
    }
}

void FPSCounter::counterLoop()
{
}

void FPSCounter::increase()
{
    m_timer->stop();
    m_lastFrameDuration = m_timer->getElapsedNs();
    m_lastFrameValue = 1000000000 / m_lastFrameDuration; // fps = 1e6 / duration.
    m_samples.add( m_lastFrameValue );
    m_timer->start();
}

double FPSCounter::getCurrentFps() const
{
    return m_lastFrameValue;
}

double FPSCounter::getAverageFps() const
{
    return m_samples.getAverage();
}

void FPSCounter::setSampleSize( size_t sampleSize )
{
    m_samples.setCapacity( sampleSize );
    m_bufferSize = sampleSize;
}

void FPSCounter::setMeasurePeriod( const unsigned periodNs )
{
    m_sleepTimeNs = periodNs;
}

double FPSCounter::normalizeToSleepTime( const double fpsCount ) const
{
    return fpsCount * 1000000.0 / (double)m_sleepTimeNs;
}

FPSCounter::~FPSCounter()
{
    stop();
}

void FPSCounter::stop()
{
    if( m_isRunning )
    {
        m_isRunning = false;
        m_mainThread.join();
    }
}

FPSCounter* FPSCounterFactory::getConcreteFPSCounter()
{
    //return new FPSCounterConcrete();
    return nullptr;
}