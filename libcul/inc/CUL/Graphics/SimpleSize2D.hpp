#pragma once

#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
struct SimpleSize2D
{
    Type width = static_cast<Type>( 0 );
    Type height = static_cast<Type>( 0 );
    const String toString() const
    {
        String result = "( width: " + String( (unsigned)width ) + ", height: " + String( (unsigned)height ) + ")";
        return result;
    }
};

using SSize2Dui = SimpleSize2D<unsigned>;
using SSize2Di = SimpleSize2D<int>;

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )