#pragma once

#include "CUL/String/StringWrapper.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
struct SimpleSize2D
{
    Type width = static_cast<Type>( 0 );
    Type height = static_cast<Type>( 0 );

    const StringWr toString() const
    {
        return StringWr::createFromPrintf( "(w: %d, h: %d)", (std::int32_t)width, (std::int32_t)height );
    }
};

using SSize2Dui = SimpleSize2D<unsigned>;
using SSize2Di = SimpleSize2D<int>;

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )