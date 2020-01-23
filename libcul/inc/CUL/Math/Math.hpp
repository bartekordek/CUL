#pragma once

#include "CUL/Math/Axis.hpp"
#include "CUL/STL_IMPORTS/STD_type_traits.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )
NAMESPACE_BEGIN( Util )

const Axis CULLib_API carthesian2Normal( const AxisCarthesian cart );
const AxisCarthesian CULLib_API normal2Carthesian( const Axis cart );

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
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_BEGIN( Constants )
static const double PI = 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647093844609550582231725359408128481;
NAMESPACE_END( Constants )

NAMESPACE_END( Util )
NAMESPACE_END( Math )
NAMESPACE_END( CUL )