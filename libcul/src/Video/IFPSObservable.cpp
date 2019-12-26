#include "CUL/Video/IFPSObservable.hpp"

using namespace CUL::Video;

IFPSObservable::IFPSObservable()
{

}

void IFPSObservable::addFPSCounter( IFPSCounter* counter )
{
    m_fpsCounter = counter;
}

void IFPSObservable::frameHasEnded()
{
    if( m_fpsCounter )
    {
        m_fpsCounter->increase();
    }
}

IFPSObservable::~IFPSObservable()
{

}