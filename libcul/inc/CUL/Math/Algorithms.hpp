#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( ALG )

CULLib_API std::vector<unsigned> fibonacciLinear( unsigned n );
CULLib_API unsigned nearestPowerOfTwo( unsigned n );

// Bytes -> KiBytes
constexpr float bytesToKiBytes( float inBytes )
{
    return inBytes / 1024.0f;
}

constexpr std::uint64_t bytesToKiBytes( std::uint64_t inBytes )
{
    return inBytes >> 10;
}

// KiBytes -> Bytes
constexpr float kiBytesToBytes( float inKiBytes )
{
    return inKiBytes * 1024.0f;
}

constexpr std::uint64_t kiBytesToBytes( std::uint64_t inKiBytes )
{
    return inKiBytes << 10;
}

// KiBytes -> MiBytes
constexpr float kiBytesToMiBytes( float inKiBytes )
{
    return inKiBytes / 1024.0f;
}

constexpr std::uint64_t kiBytesToMiBytes( std::uint64_t inKiBytes )
{
    return inKiBytes >> 10;
}

// MiBytes -> KiBytes
constexpr float miBytesToKiBytes( float inMiBytes )
{
    return inMiBytes * 1024.0f;
}

constexpr std::uint64_t miBytesToKiBytes( std::uint64_t inMiBytes )
{
    return inMiBytes << 10;
}

// Bytes -> MiBytes
constexpr float bytesToMiBytes( float inBytes )
{
    return inBytes / ( 1024.0f * 1024.0f );
}

constexpr std::uint64_t bytesToMiBytes( std::uint64_t inBytes )
{
    return inBytes >> 20;
}

// MiBytes -> Bytes
constexpr float miBytesToBytes( float inMiBytes )
{
    return inMiBytes * ( 1024.0f * 1024.0f );
}

constexpr std::uint64_t miBytesToBytes( std::uint64_t inMiBytes )
{
    return inMiBytes << 20;
}

NAMESPACE_END( ALG )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )