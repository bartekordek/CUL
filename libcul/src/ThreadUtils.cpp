#include "CUL/ThreadUtils.hpp"
#ifdef _MSC_VER
#include "ThreadUtilityWindows.hpp"
#else
#include "ThreadUtilityDummy.hpp"
#endif

void CUL::ThreadUtils::setCurrentThreadName( const String& name )
{
#ifdef _MSC_VER
    CUL::ThreadUtils::setCurrentThreadNameWin( name );
#else
    CUL::ThreadUtils::setCurrentThreadNameDummy( name );
#endif
}