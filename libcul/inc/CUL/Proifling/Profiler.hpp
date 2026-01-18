#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

#if CUL_PROFILER_PIX
namespace CUL
{
class PixRuntimeHelper
{
public:
    static PixRuntimeHelper& getInstance();

protected:
private:
    PixRuntimeHelper();
    ~PixRuntimeHelper();
};

class Profiler
{
public:
    Profiler( const char* eventName );
    static void FrameEnd();
    ~Profiler();

protected:
private:
};
}  // namespace CUL

    #define ProfileScopeVar( varName ) CUL::Profiler varName( MacroArgumentToStringLiteral( varname ) )
    #define ProfilerScope( name ) CUL::Profiler CUL_UNIQUE_VAR( profiler )( name )
    #define ProfilerScopeColor( name, color ) CUL::Profiler varName( MacroArgumentToStringLiteral( name ) )
    #define FrameEnd CUL::Profiler::FrameEnd()

#elif defined( TRACY_ENABLE )
    #include "CUL/IMPORT_tracy.hpp"
    #define ProfileScopeVar( varName ) ZoneNamed( varName, true )
    #define ProfilerScope( name ) ZoneScopedN(name)
    #define ProfilerScopeColor( name, color ) ZoneScopedNC( name, color )
    #define FrameEnd FrameMark
#else
    #define ProfileScopeVar( varName )
    #define ProfilerScope( name )
    #define ProfilerScopeColor( name, color )
    #define FrameEnd
#endif
