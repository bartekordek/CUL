#pragma once

#include "CUL/Math/Angle.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

class CULLib_API Rotation
{
public:
    Angle yaw;
    Angle pitch;
    Angle roll;

    inline Rotation& operator+=( const Rotation & rhv )
    {
        yaw += rhv.yaw;
        pitch += rhv.pitch;
        roll += rhv.roll;

        return *this;
    }

    inline Rotation& operator-=( const Rotation& rhv )
    {
        yaw -= rhv.yaw;
        pitch -= rhv.pitch;
        roll -= rhv.roll;

        return *this;
    }

protected:
private:
};

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )