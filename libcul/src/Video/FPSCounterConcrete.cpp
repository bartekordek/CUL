#include "FPSCounterConcrete.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;
using namespace Video;

FPSCounterConcrete::FPSCounterConcrete()
{
    auto print = []( const boost::circular_buffer<int>& buff )
    {
        size_t size = buff.size();
        std::cout << "\nbuff: \n";
        for( size_t i = 0; i < size; ++i )
        {
            std::cout << buff[i] << "\n";
        }
    };

    boost::circular_buffer<int> dupa( 3 );

    dupa.push_back( 1 );
    dupa.push_back( 2 );
    dupa.push_back( 3 );
    print( dupa );
    dupa.push_back( 4 );
    print( dupa );

    m_samples.set_capacity( m_bufferSize );
    m_timer.reset( CUL::TimerFactory::getChronoTimer() );
}

void FPSCounterConcrete::start()
{
    if( false == m_isRunning )
    {
        m_isRunning = true;
        m_timer->start();
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
    m_timer->stop();
    m_lastFrameDuration = m_timer->getElapsed().getMs();
    m_lastFrameValue = 1000.f / m_lastFrameDuration;
    m_samples.push_back( m_lastFrameValue );
    m_averageFps = calculateAverageFps();
    m_timer->start();
}

double FPSCounterConcrete::getCurrentFps() const
{
    return m_lastFrameValue;
}

double FPSCounterConcrete::getAverageFps() const
{
    return m_averageFps;
}

void FPSCounterConcrete::setSampleSize( unsigned short sampleSize )
{
    m_samples.resize( sampleSize );
    m_bufferSize = sampleSize;
}

void FPSCounterConcrete::setMeasurePeriod( const unsigned periodMs )
{
    m_sleepTimeMs = periodMs;
}

void FPSCounterConcrete::counterLoop()
{
    //while( m_isRunning )
    //{
    //    m_timer->sleepMiliSeconds( m_sleepTimeMs );
    //    m_samples.push_front( m_lastFrameValue );
    //    m_averageFps = calculateAverageFps();
    //}
}


FPSCounterConcrete::~FPSCounterConcrete()
{
    if( m_isRunning )
    {
        stop();
    }
}

double FPSCounterConcrete::calculateAverageFps() const
{
    if( 0 == m_samples.size() )
    {
        return 0.0;
    }

    double sum = 0.0;
    for( size_t i = 0; i < m_bufferSize; ++i )
    {
        sum += m_samples[i];
    }

    sum /= ( static_cast<decltype( sum )>( m_bufferSize ) );
    return sum;
}

double FPSCounterConcrete::normalizeToSleepTime( const double fpsCount ) const
{
    return fpsCount * 1000.0 / m_sleepTimeMs;
}