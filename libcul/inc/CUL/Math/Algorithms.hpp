#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( ALG )

CULLib_API std::vector<unsigned> fibonacciLinear( unsigned n );
CULLib_API unsigned nearestPowerOfTwo( unsigned n );

NAMESPACE_END( ALG )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )