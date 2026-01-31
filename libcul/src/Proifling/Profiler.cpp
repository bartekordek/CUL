#include "CUL/Proifling/Profiler.hpp"

#if defined( CUL_WINDOWS ) && !CUL_WINDOWS_CLANG && CUL_PROFILER_PIX
#include "IMPORT_pix.hpp"

#undef FrameEnd
namespace CUL
{
PixRuntimeHelper& PixRuntimeHelper::getInstance()
{
    static PixRuntimeHelper instance;
    return instance;
}

PixRuntimeHelper::PixRuntimeHelper()
{
    // WinPixEventRuntime::Initialize();
}

PixRuntimeHelper::~PixRuntimeHelper()
{
}

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