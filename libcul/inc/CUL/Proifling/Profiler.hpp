#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"


#if defined( CUL_PROFILER_PIX )
    #define CUL_PROFILER_PIX 1
#elif defined( TRACY_ENABLE )
    #include "CUL/IMPORT_tracy.hpp"
    #define CUL_PROFILER_PIX 0

    #define ProfileScopeVar( varName ) ZoneNamed( varName, true )
    #define ProfilerScope( name ) ZoneScopedN(name)
    #define ProfilerScopeColor( name, color ) ZoneScopedNC( name, color )
    #define FrameEnd FrameMark
#else
    #define CUL_PROFILER_PIX 0
    #define ProfileScopeVar( varName )
    #define ProfilerScope( name )
    #define ProfilerScopeColor( name, color )
    #define FrameEnd
#endif
