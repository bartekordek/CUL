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