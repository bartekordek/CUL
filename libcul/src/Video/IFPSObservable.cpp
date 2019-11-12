#include "CUL/Video/IFPSObservable.hpp"

using namespace CUL;
using namespace Video;

void IFPSObservable::addFPSCounter( IFPSCounter* counter )
{
    this->m_fpsCounter = counter;
}

void IFPSObservable::frameHasEnded()
{
    if( this->m_fpsCounter )
    {
        this->m_fpsCounter->increase();
    }
}