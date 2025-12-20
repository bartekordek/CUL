#include "CUL/Proifling/Profiler.hpp"

#if defined( CUL_WINDOWS ) && !CUL_WINDOWS_CLANG && CUL_PROFILER_PIX
#include "IMPORT_pix.hpp"

namespace CUL
{

Profiler::Profiler( const char* eventName )
{
    PIXBeginEvent( UINT64( 0 ), eventName );
}

void Profiler::FrameEnd()
{
}

Profiler::~Profiler()
{
    PIXEndEvent();
}
}  // namespace CUL

#elif defined( TRACY_ENABLE )

#endif