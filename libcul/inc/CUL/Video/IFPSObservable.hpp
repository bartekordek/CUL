#pragma once

#include "CUL/Video/FPSCounter.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Video )

class CULLib_API IFPSObservable
{
public:
    IFPSObservable();

    void addFPSCounter( FPSCounter* counter );
    void frameHasEnded();

    virtual ~IFPSObservable();

protected:
private:
    IFPSObservable( const IFPSObservable& instance ) = delete;
    IFPSObservable( IFPSObservable&& instance ) = delete;
    IFPSObservable& operator=( const IFPSObservable& instance ) = delete;
    IFPSObservable& operator=( IFPSObservable&& instance ) = delete;

    FPSCounter* m_fpsCounter = nullptr;
};

NAMESPACE_END( Video )
NAMESPACE_END( CUL )