#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
struct Rect2D
{
    Rect2D() = default;

    virtual ~Rect2D() = default;

    Rect2D(
        const Type inWidth,
        const Type inHeight,
        const Type inX,
        const Type inY ):
        width( inWidth ),
        height( inHeight ),
        x( inX ),
        y( inY )
    {
    }

    Type width = static_cast<Type>( 0 );
    Type height = static_cast<Type>( 0 );
    Type x = static_cast<Type>( 0 );
    Type y = static_cast<Type>( 0 );
};

using Rect3Df = Rect2D<float>;
using Rect3Di = Rect2D<int>;

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )