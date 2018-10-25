#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

enum class AxisCarthesian: short
{
    X,
    Y,
    Z,
    ERROR
};

enum class Axis: short
{
    WIDTH,
    HEIGHT,
    DEPTH,
    ERROR
};

const unsigned CULLib_API ac2size_t( const AxisCarthesian cart );
const unsigned CULLib_API ax2size_t( const Axis ax );

NAMESPACE_END( Math )
NAMESPACE_END( CUL )
