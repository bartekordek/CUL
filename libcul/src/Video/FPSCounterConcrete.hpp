#pragma once
#include "CUL/Video/IFPSCounter.hpp"

#include "CUL/ITimer.hpp"

#include "CUL/STD_memory.hpp"
#include "CUL/STD_atomic.hpp"
#include "CUL/STD_thread.hpp"

#include "BoostCircularBuffer.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Video )

#pragma once
#ifdef _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 4820 )
#endif

class FPSCounterConcrete:
    public IFPSCounter
{
public:
    FPSCounterConcrete();
    FPSCounterConcrete( const FPSCounterConcrete& rhv ) = delete;
    virtual ~FPSCounterConcrete();

    FPSCounterConcrete& operator=( const FPSCounterConcrete& rhv ) = delete;

    void start() override;
    void stop() override;
    void increase() override;
    const double getCurrentFps()const override;
    const double getAverageFps()const override;
    void setSampleSize( unsigned short sampleSize ) override;

protected:
private:
    void counterLoop();
    const double calculateAverageFps()const;
    unsigned int bufferSize = 4;

    std::thread mainThread;
    std::unique_ptr<CUL::ITimer> timer;
    std::atomic<bool> m_isRunning = { false };//TODO: delegate thread
    //creation to separate class, to check if thread was created and is runing.
    std::atomic<unsigned> framesCount = { 0 };
    std::atomic<unsigned> lastFrameValue = { 0 };
    boost::circular_buffer<unsigned> m_samples;
    std::atomic<double> averageFps = { 0.0 };
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( Video )
NAMESPACE_END( CUL )