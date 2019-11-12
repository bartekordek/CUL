#include "CUL/Math/Axis.hpp"

const CUL::Math::Size CUL::Math::ac2Size( const CUL::Math::AxisCarthesian cart )
{
    return static_cast< unsigned >( cart );
}

const CUL::Math::Size CUL::Math::ax2Size( const CUL::Math::Axis ax )
{
    return static_cast< unsigned >( ax );
}