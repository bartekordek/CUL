#pragma once

#include "CUL/CUL.hpp"
#include "CUL/Math/Vector3D.hpp"
#include "CUL/Filesystem/Path.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using Vector3Dd = CUL::Math::Vector3Dd;
using Path = CUL::FS::Path;

class CULLib_API ITexture
{
public:
    ITexture();
    ITexture( const ITexture& val ) = delete;

    virtual ~ITexture();

    ITexture& operator=( const ITexture& rhv ) = delete;

    virtual const Vector3Dd& getSize()const = 0;
    virtual const Path& getPath()const = 0;

protected:
private:
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )