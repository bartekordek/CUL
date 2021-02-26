#pragma once

#include "CUL/Math/Math.hpp"
#include "CUL/Math/Axis.hpp"
#include "CUL/Math/Point.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( Primitives )

#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif

using PointType = CUL::MATH::Point;
using TriangleData = std::array<PointType,3>;

class Triangle3D final
{
public:
    Triangle3D()
    {
    }

    Triangle3D( const Triangle3D& rhv ):
        m_dimensions( rhv.m_dimensions ),
        m_p( rhv.m_p ),
        m_min( rhv.m_min ),
        m_max( rhv.m_max )
    {
        calculateDimensions();
        calculateCenter();
    }

    Triangle3D(
        const Point& p1,
        const Point& p2,
        const Point& p3 )
    {
        m_p[0] = p1;
        m_p[1] = p2;
        m_p[2] = p3;

        calculateDimensions();
        calculateCenter();
    }

    Triangle3D& operator=( const Triangle3D& rhv )
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

    Triangle3D& operator +=( const Point& translationVector )
    {
        for( auto& point: m_p )
        {
            point += translationVector;
        }
        calculateDimensions();
        calculateCenter();
        return *this;
    }

    const Point& getSize() const
    {
        return m_dimensions;
    }

    Point::Type getDimension( const AxisCarthesian type ) const
    {
        return m_dimensions[static_cast<size_t>( type )];
    }

    Point::Type getDimension( const Axis type ) const
    {
        return m_dimensions[static_cast<size_t>( type )];
    }

    void setPoint(
        const Point& point,
        const AxisCarthesian axis )
    {
        Point& pointIn = m_p[static_cast<unsigned>( axis )];
        pointIn = point;
        calculateDimensions();
        calculateCenter();
    }

    const Point& getP1() const
    {
        return m_p.at( 0 );
    }

    const Point& getP2() const
    {
        return m_p.at( 1 );
    }

    const Point& getP3() const
    {
        return m_p.at( 2 );
    }

    void setP1( const Point& val )
    {
        m_p[0] = val;
    }

    void setP2( const Point& val )
    {
        m_p[1] = val;
    }

    void setP3( const Point& val )
    {
        m_p[2] = val;
    }

    const Point& getCentralPosition() const
    {
        return m_center;
    }

    void setValues( const TriangleData& values )
    {
        const auto size = values.size();
        for( size_t i = 0; i < size; ++i )
        {
            m_p[ i ] = values[ i ];
        }

        calculateDimensions();
        calculateCenter();
    }

    virtual ~Triangle3D()
    {
    }

protected:
private:
#ifdef _MSC_VER
    // Yes, I know that is a Spectre mitigation.
    // But for now, I let this as TODO, since i don't know
    // How to fix this.
    // TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
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
#ifdef _MSC_VER
#pragma warning( pop )
#endif
    void calculateCenter()
    {
        auto x = ( m_p[0][0] + m_p[1][0] + m_p[2][0] ) / m_three;
        auto y = ( m_p[0][1] + m_p[1][1] + m_p[2][1] ) / m_three;
        auto z = ( m_p[0][2] + m_p[1][2] + m_p[2][2] ) / m_three;
        m_center.x() = x;
        m_center.y() = y;
        m_center.z() = z;
    }

    Point m_dimensions;
    std::array<Point, 3> m_p;
    Point::Type m_three = 3.f;
    Point m_center;
    Point m_min;
    Point m_max;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( Primitives )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )