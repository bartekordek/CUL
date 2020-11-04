#pragma once

#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( Primitives )

template <typename Type>
class Triangle
{
public:
    Vector3D<Type> p1;
    Vector3D<Type> p2;
    Vector3D<Type> p3;

    Triangle()
    {

    }

    virtual ~Triangle()
    {

    }

protected:
private:
};

using TriangleF = Triangle<float>;
using TriangleD = Triangle<double>;
using TriangleI = Triangle<int>;
using TriangleU = Triangle<unsigned int>;

NAMESPACE_END( Primitives )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )