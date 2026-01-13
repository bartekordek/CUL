#include "CUL/Math/Utils.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"

using namespace CUL::MATH;

const glm::vec3 Utils::sphericalToVector( float xAngle, float zAngle, float r )
{
    glm::vec3 result;

    result.x = r * std::sin( xAngle ) * std::cos( zAngle );
    result.y = r * std::sin( xAngle ) * std::sin( zAngle ); 
    result.z = r * std::cos( xAngle );

    return result;
}

CULLib_API bool Utils::equals( float val1, float val2, float epsilon )
{
    return std::abs( val1 - val2 ) < epsilon;
}

CULLib_API bool Utils::equals( double val1, double val2, double epsilon )
{
    return std::abs( val1 - val2 ) < epsilon;
}

CULLib_API float Utils::floatModulo( float inValue, float moduloVal )
{
    if( inValue <= moduloVal )
    {
        return inValue;
    }

    const float count = static_cast<float>( static_cast<std::int32_t>( inValue / moduloVal ) );
    const float mul = count * moduloVal;

    return inValue - mul;
}

double Utils::floatModulo( double inValue, double moduloVal )
{
    if( inValue <= moduloVal )
    {
        return inValue;
    }

    const double count = static_cast<double>( static_cast<std::int32_t>( inValue / moduloVal ) );
    const double mul = count * moduloVal;

    return inValue - mul;
}

bool Utils::floatIsZero( float inValue )
{
    return std::abs( inValue ) <= std::numeric_limits<float>::epsilon();
}
