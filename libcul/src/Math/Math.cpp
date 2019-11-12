#include "CUL/Math/Math.hpp"

const CUL::Math::Axis CUL::Math::Util::carthesian2Normal( const CUL::Math::AxisCarthesian cart )
{
    return static_cast< CUL::Math::Axis >( cart );
}

const CUL::Math::AxisCarthesian CUL::Math::Util::normal2Carthesian( const CUL::Math::Axis cart )
{
    return static_cast< CUL::Math::AxisCarthesian >( cart );
}