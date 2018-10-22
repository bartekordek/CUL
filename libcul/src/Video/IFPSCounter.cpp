#include "CUL/Video/IFPSCounter.hpp"
#include "FPSCounterConcrete.hpp"

using namespace CUL;
using namespace Video;

IFPSCounter::IFPSCounter()
{
}

IFPSCounter::~IFPSCounter()
{
}

IFPSCounter* FPSCounterFactory::getConcreteFPSCounter()
{
    return new FPSCounterConcrete();
}