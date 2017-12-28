#pragma once
#include <CUL/CUL.hpp>
#include "CUL/ITime.hpp"
namespace CUL 
{
    class CULLib_API ITimer
    {
    public:
        ITimer();
        virtual ~ITimer();

        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void reset() = 0;
        virtual const ITime& getElapsed()const = 0;

        static void sleepSeconds( const unsigned int seconds );
        static void sleepMiliSeconds( const unsigned int mSeconds );
        static void sleepMicroSeconds( const unsigned int uSeconds );
    };

    class CULLib_API TimerFactory
    {
    public:
        static ITimer* getChronoTimer();
    private:
    };
}