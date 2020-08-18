#include "CUL/Math/Math.hpp"

CUL::MATH::Axis CUL::MATH::UTIL::carthesian2Normal( const CUL::MATH::AxisCarthesian cart )
{
    return static_cast<CUL::MATH::Axis>( cart );
}

CUL::MATH::AxisCarthesian CUL::MATH::UTIL::normal2Carthesian( const CUL::MATH::Axis cart )
{
    return static_cast<CUL::MATH::AxisCarthesian>( cart );
}
