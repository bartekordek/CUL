#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )

enum class ThreeState : std::uint8_t
{
    True = 0u,
    False,
    Undetermined
};

NAMESPACE_END( CUL )