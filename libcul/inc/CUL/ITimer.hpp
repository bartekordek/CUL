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

    static void sleepSeconds( unsigned int seconds );
    static void sleepMiliSeconds( unsigned int mSeconds );
    static void sleepMicroSeconds( unsigned int uSeconds );

    static void sleepSeconds( int seconds );
    static void sleepMiliSeconds( int mSeconds );
    static void sleepMicroSeconds( int uSeconds );

    static void sleepSeconds( float seconds );
    static void sleepMiliSeconds( float mSeconds );
    static void sleepMicroSeconds( float uSeconds );
};

class CULLib_API TimerFactory
{
public:
    static ITimer* getChronoTimer();
private:
};

NAMESPACE_END( CUL )