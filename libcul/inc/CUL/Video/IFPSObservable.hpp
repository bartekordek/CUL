#pragma once

#include "CUL/Video/IFPSCounter.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Video )

class CULLib_API IFPSObservable
{
public:
    IFPSObservable();

    void addFPSCounter( IFPSCounter* counter );
    void frameHasEnded();

    virtual ~IFPSObservable();

protected:
private:
    IFPSObservable( const IFPSObservable& instance ) = delete;
    IFPSObservable( IFPSObservable&& instance ) = delete;
    IFPSObservable& operator=( const IFPSObservable& instance ) = delete;
    IFPSObservable& operator=( IFPSObservable&& instance ) = delete;

    IFPSCounter* m_fpsCounter = nullptr;
};

NAMESPACE_END( Video )
NAMESPACE_END( CUL )