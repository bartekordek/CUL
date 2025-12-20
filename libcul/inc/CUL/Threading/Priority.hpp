#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )

enum class EPriority : uint8_t
{
    None = 0u,
    Low,
    Medium,
    High,
    COUNT
};

inline const char* EPriorityToChar( EPriority inPriority )
{
    switch( inPriority )
    {
        case CUL::EPriority::None:
            return "None";
            break;
        case CUL::EPriority::Low:
            return "Low";
            break;
        case CUL::EPriority::Medium:
            return "Medium";
            break;
        case CUL::EPriority::High:
            return "High";
            break;
        case CUL::EPriority::COUNT:
            return "Count";
            break;
        default:
            return "Default";
            break;
    }
}

NAMESPACE_END( CUL )