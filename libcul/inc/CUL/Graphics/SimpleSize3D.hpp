#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
struct SimpleSize3D
{
    Type width = static_cast<Type>( 0 );
    Type height = static_cast<Type>( 0 );
    Type depth = static_cast<Type>( 0 );
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )