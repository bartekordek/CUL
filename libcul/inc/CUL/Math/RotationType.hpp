#pragma once

#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

using RotationTypeType = unsigned short;

enum class RotationType: RotationTypeType
{
    ROLL = 0, // X - Y
    PITCH, // X - Z
    YAW, // Y - Z
    ERROR
};

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )