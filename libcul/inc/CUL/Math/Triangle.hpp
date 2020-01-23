#pragma once

#include "CUL/Math/Vector3D.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

template <typename Type>
class Triangle3D
{
public:
    Triangle3D()
    {
    }

    Triangle3D( const Triangle3D<Type>& rhv ):
        m_dimensions( rhv.m_dimensions ),
        m_p( rhv.m_p ),
        m_min( rhv.m_min ),
        m_max( rhv.m_max )
    {
        calculateDimensions();
    }

    Triangle3D(
        const Vector3D<Type>& p1,
        const Vector3D<Type>& p2,
        const Vector3D<Type>& p3 )
    {
        m_p[0] = p1;
        m_p[1] = p2;
        m_p[2] = p3;

        calculateDimensions();
    }

    Triangle3D& operator=( const Triangle3D<Type>& rhv )
    {
        if( this != &rhv )
        {
            m_dimensions = rhv.m_dimensions;
            m_p = rhv.m_p;
            m_min = rhv.m_min;
            m_max = rhv.m_max;
        }
        return *this;
    }

    Triangle3D& operator +=( const Vector3D<Type>& translationVector )
    {
        for( auto& point : m_p )
        {
            point += translationVector;
        }
        calculateDimensions();
        return *this;
    }

    virtual ~Triangle3D()
    {
    }

    const Vector3D<Type>& getSize() const
    {
        return m_dimensions;
    }

    const Type getDimension( const AxisCarthesian type ) const
    {
        return m_dimensions[type];
    }

    const Type getDimension( const Axis type ) const
    {
        return m_dimensions[static_cast<AxisCarthesian>( type )];
    }

    void setPoint(
        const Vector3D<Type>& point,
        const AxisCarthesian axis )
    {
        Vector3D<Type>& pointIn = m_p[static_cast<unsigned>( axis )];
        pointIn = point;
        calculateDimensions();
    }

    const Vector3D<Type>& getP1() const
    {
        return m_p.at( 0 );
    }

    const Vector3D<Type>& getP2() const
    {
        return m_p.at( 1 );
    }

    const Vector3D<Type>& getP3() const
    {
        return m_p.at( 2 );
    }

protected:
private:
    void calculateDimensions()
    {
        for( auto i = static_cast<unsigned>( AxisCarthesian::X );
            i <= static_cast<unsigned>( AxisCarthesian::Z );
            ++i )
        {
            auto cartIndex = static_cast<AxisCarthesian>( i );
            m_min.setAxisValue( cartIndex, min( m_p[0], m_p[1], m_p[2], cartIndex ) );
            m_max.setAxisValue( cartIndex, max( m_p[0], m_p[1], m_p[2], cartIndex ) );
        }

        m_dimensions = m_max - m_min;
    }

    Vector3D<Type> m_dimensions;
    std::array<Vector3D<Type>, 3> m_p;
    Vector3D<Type> m_min;
    Vector3D<Type> m_max;
};

using Triangle3DI = Triangle3D<int>;
using Triangle3DD = Triangle3D<double>;
using Triangle3DF = Triangle3D<float>;

NAMESPACE_END( Math )
NAMESPACE_END( CUL )