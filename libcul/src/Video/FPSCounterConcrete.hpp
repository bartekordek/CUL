#pragma once
#include "CUL/Video/IFPSCounter.hpp"

#include "CUL/ITimer.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_atomic.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"

#include "BoostCircularBuffer.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Video )

#pragma once
#ifdef _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 4820 )
#endif

class FPSCounterConcrete final:
    public IFPSCounter
{
public:
    FPSCounterConcrete();

    ~FPSCounterConcrete();

    void start() override;
    void stop() override;
    void increase() override;
    double getCurrentFps() const override;
    double getAverageFps() const override;
    void setSampleSize( size_t sampleSize ) override;
    void setMeasurePeriod( const unsigned periodMs ) override;

protected:
private:
    void counterLoop();
    double calculateAverageFps() const;
    double normalizeToSleepTime( const double fpsCount ) const;
    size_t m_bufferSize = 16;

    std::thread m_mainThread;
    std::unique_ptr<CUL::ITimer> m_timer;
    std::atomic<bool> m_isRunning = { false };//TODO: delegate thread
    //creation to separate class, to check if thread was created and is runing.
    std::atomic<float> m_lastFrameValue = { 0.f };
    std::atomic<float> m_lastFrameDuration = { 0.f };
    boost::circular_buffer<float> m_samples;
    std::atomic<double> m_averageFps = { 0.0 };
    std::atomic<unsigned> m_sleepTimeMs = { 1000 };

private: // Deleted.
    FPSCounterConcrete( FPSCounterConcrete&& arg ) = delete;
    FPSCounterConcrete( const FPSCounterConcrete& value ) = delete;
    FPSCounterConcrete& operator=( const FPSCounterConcrete& rhv ) = delete;
    FPSCounterConcrete& operator=( FPSCounterConcrete&& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( Video )
NAMESPACE_END( CUL )