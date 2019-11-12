#pragma once

#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

enum class RotationType
{
    ROLL = 0, // X - Y
    PITCH, // X - Z
    YAW, // Y - Z
    ERROR
};

NAMESPACE_END( Math )
NAMESPACE_END( CUL )