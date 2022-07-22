#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_stddef.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Video )

class CULLib_API IFPSCounter
{
public:
    IFPSCounter();
    virtual ~IFPSCounter();

    virtual double getCurrentFps() const = 0;
    virtual double getAverageFps() const = 0;
    virtual void setSampleSize( size_t sampleSize ) = 0;
    virtual void setMeasurePeriod( const unsigned periodMs ) = 0;

    virtual void increase() = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

protected:
private:
    IFPSCounter( const IFPSCounter& arg ) = delete;
    IFPSCounter& operator=( const IFPSCounter& rhv ) = delete;
};

class CULLib_API FPSCounterFactory
{
public:
    static IFPSCounter* getConcreteFPSCounter();
protected:
private:
    FPSCounterFactory() = delete;
    FPSCounterFactory( const FPSCounterFactory& arg ) = delete;
    FPSCounterFactory& operator=( const FPSCounterFactory& rhv ) = delete;
    ~FPSCounterFactory() = delete;
};

NAMESPACE_END( Video )
NAMESPACE_END( CUL )