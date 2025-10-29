#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )

enum class EPriority : std::uint8_t
{
    None = 0u,
    Low,
    Medium,
    High,
    COUNT
};

NAMESPACE_END( CUL )