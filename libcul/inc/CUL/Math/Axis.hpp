#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

using Size = unsigned;

#ifdef _MSC_VER
// For now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 4574 )
#endif
#ifdef ERROR
#undef ERROR
#endif
#ifdef _MSC_VER
#pragma warning( pop )
#endif

enum class AxisCarthesian: short
{
    X = 0,
    Y,
    Z,
    ERROR
};

enum class Axis: short
{
    WIDTH = 0,
    HEIGHT,
    DEPTH,
    ERROR
};

Size CULLib_API ac2Size( const AxisCarthesian cart );
Size CULLib_API ax2Size( const Axis ax );

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )