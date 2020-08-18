#pragma once

#include "CUL/Math/Math.hpp"
#include "CUL/Math/Axis.hpp"
#include "CUL/Math/Point.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif

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
        calculateCenter();
    }

    Triangle3D(
        const Point<Type>& p1,
        const Point<Type>& p2,
        const Point<Type>& p3 )
    {
        m_p[0] = p1;
        m_p[1] = p2;
        m_p[2] = p3;

        calculateDimensions();
        calculateCenter();
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

    Triangle3D& operator +=( const Point<Type>& translationVector )
    {
        for( auto& point: m_p )
        {
            point += translationVector;
        }
        calculateDimensions();
        calculateCenter();
        return *this;
    }

    const Point<Type>& getSize() const
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
        const Point<Type>& point,
        const AxisCarthesian axis )
    {
        Point<Type>& pointIn = m_p[static_cast<unsigned>( axis )];
        pointIn = point;
        calculateDimensions();
        calculateCenter();
    }

    const Point<Type>& getP1() const
    {
        return m_p.at( 0 );
    }

    const Point<Type>& getP2() const
    {
        return m_p.at( 1 );
    }

    const Point<Type>& getP3() const
    {
        return m_p.at( 2 );
    }

    void setP1( const Point<Type>& val )
    {
        m_p[0] = val;
    }

    void setP2( const Point<Type>& val )
    {
         m_p[0] = val;
    }

    void setP3( const Point<Type>& val )
    {
        m_p[0] = val;
    }

    const Point<Type>& getCentralPosition() const
    {
        return m_center;
    }

    virtual ~Triangle3D()
    {
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
            m_min.setAxisValue( cartIndex, UTIL::min(
                m_p[0].getValue( cartIndex ),
                m_p[1].getValue( cartIndex ),
                m_p[2].getValue( cartIndex ) ) );

            m_max.setAxisValue( cartIndex, UTIL::max( 
                m_p[0].getValue( cartIndex ),
                m_p[1].getValue( cartIndex ),
                m_p[2].getValue( cartIndex ) ) );
        }

        m_dimensions = m_max - m_min;
    }

    void calculateCenter()
    {
        auto x = ( m_p[0].x + m_p[1].x + m_p[2].x ) / m_three;
        auto y = ( m_p[0].y + m_p[1].y + m_p[2].y ) / m_three;
        auto z = ( m_p[0].z + m_p[1].z + m_p[2].z ) / m_three;
        m_center.x = x;
        m_center.y = y;
        m_center.z = z;
    }

    Point<Type> m_dimensions;
    std::array<Point<Type>, 3> m_p;
    Type m_three = static_cast<Type>( 3 );
    Point<Type> m_center;
    Point<Type> m_min;
    Point<Type> m_max;
};

using Triangle3DI = Triangle3D<int>;
using Triangle3DD = Triangle3D<double>;
using Triangle3DF = Triangle3D<float>;

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )
