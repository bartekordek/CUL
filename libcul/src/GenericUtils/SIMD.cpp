#include "CUL/GenericUtils/SIMD.hpp"

namespace ispc
{
extern "C"
{
    extern void dotProduct( const float v1[], const float v2[], int count, float vout[] );
    extern void sum( const float* v1, const float* v2, int count, float* vout );
}
}  // namespace ispc

namespace CUL::GUTILS
{
void dotProduct( const float v1[], const float v2[], int count, float vout[] )
{
    ispc::dotProduct( v1, v2, count, vout );
}

void sum( const float v1[], const float v2[], int count, float vout[] )
{
    ispc::sum( v1, v2, count, vout );
}
}  // namespace CUL::GUTILS
