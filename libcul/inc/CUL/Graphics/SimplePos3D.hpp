#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
struct SimplePos3D
{
    Type x = static_cast<Type>( 0 );
    Type y = static_cast<Type>( 0 );
    Type z = static_cast<Type>( 0 );
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )