#pragma once

#include "CUL/CUL.hpp"
#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )

NAMESPACE_BEGIN( FS )
class Path;
NAMESPACE_END( FS )

NAMESPACE_BEGIN( Graphics )

using Vector3Dd = CUL::MATH::Vector3Dd;

class CULLib_API ITexture
{
public:
    ITexture();
    ITexture( const ITexture& val ) = delete;

    virtual ~ITexture();

    ITexture& operator=( const ITexture& rhv ) = delete;

    virtual const Vector3Dd& getSize() const = 0;
    virtual const FS::Path& getPath() const = 0;

protected:
private:
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )