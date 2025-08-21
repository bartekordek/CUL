#include "CUL/Proifling/Profiler.hpp"
#include "IMPORT_pix.hpp"

using namespace CUL;

#if defined(CUL_WINDOWS) && !CUL_WINDOWS_CLANG

Profiler::Profiler( const char* eventName )
{
    PIXBeginEvent( UINT64(0), eventName);
}

Profiler::~Profiler()
{
    PIXEndEvent();
}

#else
Profiler::Profiler( const char* )
{
}

Profiler::~Profiler()
{
}
#endif