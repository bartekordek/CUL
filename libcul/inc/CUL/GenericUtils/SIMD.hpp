#pragma once

#include "CUL/CUL.hpp"

namespace CUL::GUTILS
{
CULLib_API void dotProduct( const float* v1, const float* v2, int count, float* vout );
CULLib_API void sum( const float* v1, const float* v2, int count, float* vout );
}  // namespace CUL::GUTILS