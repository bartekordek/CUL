#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )

NAMESPACE_BEGIN( LOG )
class ILogger;
NAMESPACE_END( LOG )

class Time;

class CULLib_API ITimer
{
public:
    ITimer( LOG::ILogger* logger );
    virtual ~ITimer();

    virtual void start() = 0;
    virtual bool getIsStarted() const = 0;
    virtual void stop() = 0;
    virtual void reset() = 0;
    virtual const Time& getElapsed() const = 0;
    virtual std::int64_t getElapsedNs() const = 0;

    virtual void runEveryPeriod( std::function<void(void)> callback, unsigned uSeconds ) = 0;

    static void sleepSeconds( unsigned int seconds );
    static void sleepMiliSeconds( unsigned int mSeconds );
    static void sleepMicroSeconds( unsigned int uSeconds );

    static void sleepSeconds( int seconds );
    static void sleepMiliSeconds( int mSeconds );
    static void sleepMicroSeconds( int uSeconds );
    static void sleepNanoSeconds(std::int64_t ns);

    static void sleepSeconds( float seconds );
    static void sleepMiliSeconds( float mSeconds );
    static void sleepMicroSeconds( float uSeconds );

protected:
    LOG::ILogger* getLogger() const;

private:
    LOG::ILogger* m_logger = nullptr;
};

class CULLib_API TimerFactory
{
public:
    static ITimer* getChronoTimerPtr( LOG::ILogger* logger );

private:
};

NAMESPACE_END( CUL )