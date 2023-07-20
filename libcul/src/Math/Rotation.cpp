#include "CUL/Math/Rotation.hpp"
#include "CUL/Math/Math.hpp"

using namespace CUL;
using namespace MATH;

Rotation::Rotation( const glm::quat& q )
{
    // roll (x-axis rotation)
    float sinr_cosp = 2.f * ( q.w * q.x + q.y * q.z );
    float cosr_cosp = 1.f - 2.f * ( q.x * q.x + q.y * q.y );
    Roll = std::atan2( sinr_cosp, cosr_cosp );

    // pitch (y-axis rotation)
    float sinp = 2.f * ( q.w * q.y - q.z * q.x );
    if( std::abs( sinp ) >= 1.f )
        Pitch = std::copysign( (float)CUL::MATH::UTIL::Constants::PI / 2.f, sinp ); // use 90 degrees if out of range
    else
        Pitch = std::asin( sinp );

    // yaw (z-axis rotation)
    float siny_cosp = 2 * ( q.w * q.z + q.x * q.y );
    float cosy_cosp = 1 - 2 * ( q.y * q.y + q.z * q.z );
    Yaw = std::atan2( siny_cosp, cosy_cosp );
}

Rotation Rotation::operator+( const Rotation& rhv ) const
{
    Rotation result( *this );

    result.Pitch += rhv.Pitch;
    result.Yaw += rhv.Yaw;
    result.Roll += rhv.Roll;

    return result;
}

Rotation Rotation::operator-( const Rotation& rhv ) const
{
    Rotation result( *this );

    result.Pitch -= rhv.Pitch;
    result.Yaw -= rhv.Yaw;
    result.Roll -= rhv.Roll;

    return result;
}

void Rotation::reset()
{
    Pitch.reset();
    Yaw.reset();
    Roll.reset();
}

glm::quat Rotation::toQuat() const
{
    glm::quat result;
    const float pitch = Pitch.getRad();
    const float yaw = Yaw.getRad();
    const float roll = Roll.getRad();

    const float cr = std::cos( roll * 0.5f );
    const float sr = std::sin( roll * 0.5f );
    const float cp = std::cos( pitch * 0.5f );
    const float sp = std::sin( pitch * 0.5f );
    const float cy = std::cos( yaw * 0.5f );
    const float sy = std::sin( yaw * 0.5f );

    result.w = cr * cp * cy + sr * sp * sy;
    result.x = sr * cp * cy - cr * sp * sy;
    result.y = cr * sp * cy + sr * cp * sy;
    result.z = cr * cp * sy - sr * sp * cy;

    return result;
}

Rotation& Rotation::operator+=( const Rotation& rhv )
{
    Yaw += rhv.Yaw;
    Pitch += rhv.Pitch;
    Roll += rhv.Roll;

    return *this;
}

Rotation& Rotation::operator-=( const Rotation& rhv )
{
    Yaw -= rhv.Yaw;
    Pitch -= rhv.Pitch;
    Roll -= rhv.Roll;

    return *this;
}