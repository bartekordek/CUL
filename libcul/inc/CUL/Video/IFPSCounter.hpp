#pragma once
#include "CUL/UselessMacros.hpp"
#include "CUL/CUL.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Video )

class CULLib_API IFPSCounter
{
public:
    IFPSCounter();
    virtual ~IFPSCounter();

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void increase() = 0;
    virtual const double getCurrentFps()const = 0;
    virtual const double getAverageFps()const = 0;
    virtual void setSampleSize( unsigned short sampleSize ) = 0;
};

class CULLib_API FPSCounterFactory
{
public:
    static IFPSCounter* getConcreteFPSCounter();
protected:
private:
};

NAMESPACE_END( Video )
NAMESPACE_END( CUL )