#include "CUL/Math/Axis.hpp"

CUL::MATH::Size CUL::MATH::ac2Size( const CUL::MATH::AxisCarthesian cart )
{
    return static_cast<unsigned>( cart );
}

CUL::MATH::Size CUL::MATH::ax2Size( const CUL::MATH::Axis ax )
{
    return static_cast<unsigned>( ax );
}