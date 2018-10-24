#pragma once

#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )
NAMESPACE_BEGIN( Util )

/*
const Axis carthesian2Normal( const AxisCarthesian cart )
{
    if( AxisCarthesian::X == cart )
    {
        return Axis::WIDTH;
    }

    if( AxisCarthesian::Y == cart )
    {
        return Axis::HEIGHT;
    }

    if( AxisCarthesian::Z == cart )
    {
        return Axis::DEPTH;
    }

    return Axis::ERROR;
}

const AxisCarthesian normal2Carthesian( const Axis cart )
{
    if( Axis::WIDTH == cart )
    {
        return AxisCarthesian::X;
    }

    if( Axis::HEIGHT == cart )
    {
        return AxisCarthesian::Y;
    }

    if( Axis::DEPTH == cart )
    {
        return AxisCarthesian::Z;
    }

    return AxisCarthesian::ERROR;
}
*/
template<typename Type>
Type abs( const Type arg )
{
    if( arg < 0 )
    {
        return 0 - arg;
    }
    return arg;
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
const Type max( const Type val1, const Type val2 )
{
    if( val1 > val2 )
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
const Type min( const Type val1, const Type val2 )
{
    if( val1 < val2 )
    {
        return val1;
    }
    return val2;
}

NAMESPACE_BEGIN( Constants )
static const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481;
NAMESPACE_END( Constants )

NAMESPACE_END( Util )
NAMESPACE_END( Math )
NAMESPACE_END( CUL )