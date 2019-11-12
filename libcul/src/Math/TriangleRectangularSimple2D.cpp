#include "CUL/Math/TriangleRectangularSimple2D.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"

using namespace CUL;
using namespace Math;

TriangleRectangularSimple2D::TriangleRectangularSimple2D( void )
{
}

TriangleRectangularSimple2D::TriangleRectangularSimple2D( const TriangleRectangularSimple2D& value ):
    m_opposite( value.m_opposite ),
    m_adjacent( value.m_adjacent ),
    m_hypotenuse( value.m_hypotenuse ),
    m_angle( value.m_angle )
{
}

TriangleRectangularSimple2D::~TriangleRectangularSimple2D( void )
{
}

TriangleRectangularSimple2D& TriangleRectangularSimple2D::operator=( const TriangleRectangularSimple2D& rhv )
{
    if( this != &rhv )
    {
        this->m_opposite = rhv.m_opposite;
        this->m_adjacent = rhv.m_adjacent;
        this->m_hypotenuse = rhv.m_hypotenuse;
        this->m_angle = rhv.m_angle;
    }
    return *this;
}

void TriangleRectangularSimple2D::setOpposite( const double value )
{
    this->m_opposite = value;
    if( this->isLessThanEpislon( this->m_adjacent ) )
    {
        this->m_hypotenuse = this->m_opposite;
    }
    calculateQuarter();
    calculateAngle();
}

void TriangleRectangularSimple2D::setAdjacent( const double value )
{
    this->m_adjacent = value;
    if( this->isLessThanEpislon( this->m_opposite ) )
    {
        this->m_hypotenuse = this->m_adjacent;
    }
    calculateQuarter();
    calculateAngle();
}

void TriangleRectangularSimple2D::setHypotenuse( const double value )
{
    const auto ratio = value / this->m_hypotenuse;
    this->m_hypotenuse = value;
    this->m_adjacent *= ratio;
    this->m_opposite *= ratio;
    calculateQuarter();
    calculateAngle();
}

const double TriangleRectangularSimple2D::getOpposite( void )
{
    return this->m_opposite;
}

const double TriangleRectangularSimple2D::getAdjacent( void )
{
    return this->m_adjacent;
}

const double TriangleRectangularSimple2D::getHypotenuse( void )
{
    return this->m_hypotenuse;
}

const double TriangleRectangularSimple2D::calculateOpposite( void )
{
    const auto sq = this->m_hypotenuse * this->m_hypotenuse - this->m_adjacent * this->m_adjacent;
    this->m_opposite = std::sqrt( sq );
    return this->m_opposite;
}

const double TriangleRectangularSimple2D::calculateAdjacent( void )
{
    const auto sq = this->m_hypotenuse * this->m_hypotenuse - this->m_opposite * this->m_opposite;
    this->m_adjacent = std::sqrt( sq );
    return this->m_adjacent;
}

const double TriangleRectangularSimple2D::calculateHypotenuse( void )
{
    const auto sq = this->m_opposite * this->m_opposite + this->m_adjacent * this->m_adjacent;
    this->m_hypotenuse = std::sqrt( sq );
    return this->m_hypotenuse;
}

const Angle& TriangleRectangularSimple2D::getAngle( void ) const
{
    return this->m_angle;
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif
void TriangleRectangularSimple2D::calculateAngle( void )
{
    if( std::abs( this->m_adjacent ) < getEpsilon() )
    {
        const auto height = this->m_opposite;
        if( this->isLessThanEpislon( height ) )
        {
            this->m_angle.setValue( 0 );
        }
        else if( height > 0 )
        {
            this->m_angle.setValue( 90, Angle::Type::DEGREE );
        }
        else
        {
            this->m_angle.setValue( 270, Angle::Type::DEGREE );
        }
    }
    else
    {
        if( std::abs( m_opposite ) < getEpsilon() )
        {
            const auto width = std::max( this->m_adjacent, this->m_hypotenuse );
            if( width > 0 )
            {
                this->m_angle.setValue( 0 );
            }
            else
            {
                this->m_angle.setValue( 180, Angle::Type::DEGREE );
            }
        }
        else
        {
            const auto tangensAlpha = this->m_opposite / this->m_adjacent;
            const auto alphaRad = std::atan( tangensAlpha );
            if( 2 == this->m_quarter )
            {
                const auto alphaDeg = radian2degree( alphaRad );
                this->m_angle.setValue( 180 + alphaDeg, Angle::Type::DEGREE );
            }
            else if ( 3 == this->m_quarter )
            {
                const auto alphaDeg = radian2degree( alphaRad );
                this->m_angle.setValue( 180 + alphaDeg, Angle::Type::DEGREE );
            }
            else if( 4 == this->m_quarter )
            {
                const auto alphaDeg = radian2degree( alphaRad );
                this->m_angle.setValue( 360 + alphaDeg, Angle::Type::DEGREE );
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

void TriangleRectangularSimple2D::calculateQuarter( void )
{
    if( m_adjacent >= 0 )
    {
        if( m_opposite >= 0 )
        {
            this->m_quarter = 1;
        }
        else
        {
            this->m_quarter = 4;
        }
    }
    else
    {
        if( m_opposite >= 0 )
        {
            this->m_quarter = 2;
        }
        else
        {
            this->m_quarter = 3;
        }
    }
}