#pragma once

#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

enum class RotationType: size_t
{
    ROLL = 0, // X - Y
    PITCH, // X - Z
    YAW, // Y - Z
    ERROR
};

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )