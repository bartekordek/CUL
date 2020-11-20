#pragma once

#include "CUL/ITime.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API ITimer
{
public:
    ITimer();
    virtual ~ITimer();

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void reset() = 0;
    virtual const ITime& getElapsed() const = 0;

    static void sleepSeconds( const unsigned int seconds );
    static void sleepMiliSeconds( const unsigned int mSeconds );
    static void sleepMicroSeconds( const unsigned int uSeconds );

    static void sleepSeconds( const int seconds );
    static void sleepMiliSeconds( const int mSeconds );
    static void sleepMicroSeconds( const int uSeconds );
};

class CULLib_API TimerFactory
{
public:
    static ITimer* getChronoTimer();
private:
};

NAMESPACE_END( CUL )