#include "CUL/Math/Vec3.hpp"

using namespace CUL;
using namespace MATH;

CULLib_API float Vec3::getX() const
{
    return m_value.x;
}

CULLib_API float Vec3::getY() const
{
    return m_value.y;
}

CULLib_API float Vec3::getZ() const
{
    return m_value.z;
}

CULLib_API void Vec3::setX( float val )
{
    m_value.x = val;
}

CULLib_API void Vec3::setY( float val )
{
    m_value.y = val;
}

CULLib_API void Vec3::setZ( float val )
{
    m_value.z = val;
}

CULLib_API void Vec3::setXYZ( float x, float y, float z )
{
    m_value.x = x;
    m_value.y = y;
    m_value.z = z;
}

CULLib_API const glm::vec3& Vec3::getValue() const
{
    return m_value;
}