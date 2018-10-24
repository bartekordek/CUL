#pragma once

#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

template <typename Type>
class Triangle
{
public:
    Triangle()
    {

    }

    virtual ~Triangle()
    {

    }

    const Type getDimension( const AxisCarthesian type )const
    {

    }

    const Type getDimension( const Axis type )const
    {

    }

    void setDimension( const AxisCarthesian )
    {

    }

    void setDimension( const Axis )
    {

    }

protected:
private:
    void calculateDimensions()
    {

    }

    Vector3D<Type> m_dimensions;
    Vector3D<Type> m_p1;
    Vector3D<Type> m_p2;
    Vector3D<Type> m_p3;

};

NAMESPACE_END( Math )
NAMESPACE_END( CUL )