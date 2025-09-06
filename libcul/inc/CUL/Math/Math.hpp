#pragma once

#include "CUL/Math/Axis.hpp"
#include "CUL/STL_IMPORTS/STD_type_traits.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( UTIL )

Axis CULLib_API carthesian2Normal( const AxisCarthesian cart );
AxisCarthesian CULLib_API normal2Carthesian( const Axis cart );

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
template <typename Type>
const Type max( const Type val1, const Type val2 )
{
    if( val1 > val2 )
    {
        return val1;
    }
    return val2;
}

template <typename Type>
const Type max( const Type val1, const Type val2, const Type val3 )
{
    const auto v1v2 = max( val1, val2 );
    if( v1v2 > val3 )
    {
        return v1v2;
    }
    return val3;
}

template <typename Type>
const Type min( const Type val1, const Type val2 )
{
    if( val1 < val2 )
    {
        return val1;
    }
    return val2;
}

template <typename Type>
const Type min( const Type val1, const Type val2, const Type val3 )
{
    const auto v1v2 = min( val1, val2 );
    if( v1v2 < val3 )
    {
        return v1v2;
    }
    return val3;
}

template <typename Type>
Type lerp(Type a, Type b, Type f)
{
    return a + f * ( b - a );
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif
NAMESPACE_END( UTIL )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )