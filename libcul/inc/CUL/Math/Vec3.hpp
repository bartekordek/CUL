#pragma once

#include "CUL/GenericUtils/SimpleDelegate.hpp"
#include "CUL/IMPORT_GLM.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

class Vec3 final
{
public:
    CULLib_API float getX() const;
    CULLib_API float getY() const;
    CULLib_API float getZ() const;

    CULLib_API void setX( float val );
    CULLib_API void setY( float val );
    CULLib_API void setZ( float val );

    CULLib_API void setXYZ( float x, float y, float z );

    CULLib_API const glm::vec3& getValue() const;

protected:
private:
    glm::vec3 m_value = { 0.f, 0.f, 0.f };
};

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )