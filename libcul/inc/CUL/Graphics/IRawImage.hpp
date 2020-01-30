#pragma once

#include "CUL/CUL.hpp"
#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using Cunt = const unsigned int;
using RawDataPtr = unsigned char*;

class CULLib_API IRawImage
{
public:
    IRawImage() = default;
    virtual ~IRawImage() = default;
    virtual Cunt getID() const = 0;
    virtual const MATH::Vector3Du& getSize() const = 0;
    virtual RawDataPtr getData() const = 0;

protected:
private:
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )