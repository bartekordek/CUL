#pragma once

#include "CUL/ITimer.hpp"

#include "CUL/Math/VariableWithAverageValue.hpp"
#include "CUL/Memory/UniquePtrOnStack.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/STL_IMPORTS/STD_atomic.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_stddef.hpp"

NAMESPACE_BEGIN( CUL )

class TimerChrono;

NAMESPACE_BEGIN( Video )

class CULLib_API FPSCounter
{
public:
    FPSCounter();

    virtual double getCurrentFps() const;
    virtual double getAverageFps() const;
    virtual void setSampleSize( size_t sampleSize );
    virtual void setMeasurePeriod( const unsigned periodMs );

    virtual void increase();

    virtual void start();
    virtual void stop();

    virtual ~FPSCounter();
protected:
private:
    void counterLoop();
    double normalizeToSleepTime( const double fpsCount ) const;

    size_t m_bufferSize = 16;

    std::thread m_mainThread;
    Memory::UniquePtrOnStack<TimerChrono, 48> m_timer;
    std::atomic<bool> m_isRunning = { false };//TODO: delegate thread
    //creation to separate class, to check if thread was created and is runing.
    std::atomic<float> m_lastFrameValue = { 0.f };
    std::atomic<float> m_lastFrameDuration = { 0.f };
    MATH::VariableWithAverageValue m_samples;
    std::atomic<unsigned> m_sleepTimeMs = { 1000 };


    FPSCounter( const FPSCounter& arg ) = delete;
    FPSCounter( FPSCounter&& arg ) = delete;
    FPSCounter& operator=( const FPSCounter& rhv ) = delete;
    FPSCounter& operator=( FPSCounter&& rhv ) = delete;
};

class CULLib_API FPSCounterFactory
{
public:
    static FPSCounter* getConcreteFPSCounter();
protected:
private:
    FPSCounterFactory() = delete;
    FPSCounterFactory( const FPSCounterFactory& arg ) = delete;
    FPSCounterFactory& operator=( const FPSCounterFactory& rhv ) = delete;
    ~FPSCounterFactory() = delete;
};

NAMESPACE_END( Video )
NAMESPACE_END( CUL )