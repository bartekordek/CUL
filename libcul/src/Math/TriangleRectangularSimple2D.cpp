#include "CUL/Math/TriangleRectangularSimple2D.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

using namespace CUL;
using namespace MATH;

TriangleRectangularSimple2D::TriangleRectangularSimple2D()
{
}

TriangleRectangularSimple2D::TriangleRectangularSimple2D( const TriangleRectangularSimple2D& value ):
    m_opposite( value.m_opposite ),
    m_adjacent( value.m_adjacent ),
    m_hypotenuse( value.m_hypotenuse ),
    m_angle( value.m_angle )
{
}

TriangleRectangularSimple2D::~TriangleRectangularSimple2D()
{
}

TriangleRectangularSimple2D& TriangleRectangularSimple2D::operator=( const TriangleRectangularSimple2D& rhv )
{
    if( this != &rhv )
    {
        m_opposite = rhv.m_opposite;
        m_adjacent = rhv.m_adjacent;
        m_hypotenuse = rhv.m_hypotenuse;
        m_angle = rhv.m_angle;
    }
    return *this;
}

void TriangleRectangularSimple2D::setOpposite( const double value )
{
    m_opposite = value;
    if( isLessThanEpislon( m_adjacent ) )
    {
        m_hypotenuse = m_opposite;
    }
    calculateQuarter();
    calculateAngle();
}

void TriangleRectangularSimple2D::setAdjacent( const double value )
{
    m_adjacent = value;
    if( isLessThanEpislon( m_opposite ) )
    {
        m_hypotenuse = m_adjacent;
    }
    calculateQuarter();
    calculateAngle();
}

void TriangleRectangularSimple2D::setHypotenuse( const double value )
{
    const auto ratio = value / m_hypotenuse;
    m_hypotenuse = value;
    m_adjacent *= ratio;
    m_opposite *= ratio;
    calculateQuarter();
    calculateAngle();
}

const double TriangleRectangularSimple2D::getOpposite()
{
    return m_opposite;
}

const double TriangleRectangularSimple2D::getAdjacent()
{
    return m_adjacent;
}

const double TriangleRectangularSimple2D::getHypotenuse()
{
    return m_hypotenuse;
}

const double TriangleRectangularSimple2D::calculateOpposite()
{
    const auto sq = m_hypotenuse * m_hypotenuse - m_adjacent * m_adjacent;
    m_opposite = std::sqrt( sq );
    return m_opposite;
}

const double TriangleRectangularSimple2D::calculateAdjacent()
{
    const auto sq = m_hypotenuse * m_hypotenuse - m_opposite * m_opposite;
    m_adjacent = std::sqrt( sq );
    return m_adjacent;
}

const double TriangleRectangularSimple2D::calculateHypotenuse()
{
    const auto sq = m_opposite * m_opposite + m_adjacent * m_adjacent;
    m_hypotenuse = std::sqrt( sq );
    return m_hypotenuse;
}

const Angle& TriangleRectangularSimple2D::getAngle() const
{
    return m_angle;
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
void TriangleRectangularSimple2D::calculateAngle()
{
    if( std::abs( m_adjacent ) < getEpsilon() )
    {
        const auto height = m_opposite;
        if( isLessThanEpislon( height ) )
        {
            m_angle.setValue( 0 );
        }
        else if( height > 0 )
        {
            m_angle.setValue( 90, Angle::Type::DEGREE );
        }
        else
        {
            m_angle.setValue( 270, Angle::Type::DEGREE );
        }
    }
    else
    {
        if( std::abs( m_opposite ) < getEpsilon() )
        {
            const auto width = std::max( m_adjacent, m_hypotenuse );
            if( width > 0 )
            {
                m_angle.setValue( 0 );
            }
            else
            {
                m_angle.setValue( 180, Angle::Type::DEGREE );
            }
        }
        else
        {
            const auto tangensAlpha = m_opposite / m_adjacent;
            const auto alphaRad = std::atan( tangensAlpha );
            if( 2 == m_quarter )
            {
                const auto alphaDeg = radian2degree( alphaRad );
                m_angle.setValue( 180 + alphaDeg, Angle::Type::DEGREE );
            }
            else if( 3 == m_quarter )
            {
                const auto alphaDeg = radian2degree( alphaRad );
                m_angle.setValue( 180 + alphaDeg, Angle::Type::DEGREE );
            }
            else if( 4 == m_quarter )
            {
                const auto alphaDeg = radian2degree( alphaRad );
                m_angle.setValue( 360 + alphaDeg, Angle::Type::DEGREE );
            }
            else
            {
                m_angle.setValue( alphaRad, Angle::Type::RADIAN );
            }
        }
    }
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

void TriangleRectangularSimple2D::calculateQuarter()
{
    if( m_adjacent >= 0 )
    {
        if( m_opposite >= 0 )
        {
            m_quarter = 1;
        }
        else
        {
            m_quarter = 4;
        }
    }
    else
    {
        if( m_opposite >= 0 )
        {
            m_quarter = 2;
        }
        else
        {
            m_quarter = 3;
        }
    }
}
