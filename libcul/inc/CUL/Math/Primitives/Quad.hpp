#pragma once

#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

template <typename Type>
class Quad
{
public:
    Quad()
    {

    }



    virtual ~Quad()
    {

    }

    Vector3D<Type> p1;
    Vector3D<Type> p2;
    Vector3D<Type> p3;
    Vector3D<Type> p4;

protected:
private:
};

using QuadF = Quad<float>;
using QuadD = Quad<double>;
using QuadI = Quad<int>;
using QuadUi = Quad<unsigned int>;

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )