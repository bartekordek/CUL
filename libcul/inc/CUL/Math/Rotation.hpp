#pragma once

#include "CUL/Math/Angle.hpp"
#include "CUL/IMPORT_GLM.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

class CULLib_API Rotation
{
public:
    Angle Pitch;
    Angle Yaw;
    Angle Roll;

    Rotation() = default;
    Rotation( const glm::quat& qyat );

    glm::quat toQuat() const;

    Rotation& operator+=( const Rotation& rhv );
    Rotation& operator-=( const Rotation& rhv );

    ~Rotation() = default;

protected:
private:
};

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )