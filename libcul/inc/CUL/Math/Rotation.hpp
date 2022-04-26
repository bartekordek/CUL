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

protected:
private:
};

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )