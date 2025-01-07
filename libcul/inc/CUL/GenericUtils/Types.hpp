#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )

enum class ETypes: std::uint16_t
{
    Unkown = 0,
    Float,
    Double,
    Uint8,
    Int8,
    Uint16,
    Int16,
    Uint32,
    Int32,
    Uint64,
    Int64
};

NAMESPACE_END( CUL )
