#pragma once

#include "CUL/Math/Angle.hpp"
#include "CUL/Math/Epsilon.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class CULLib_API TriangleRectangularSimple2D:
    public Epsilon<double>
{
public:
    TriangleRectangularSimple2D( void );
    TriangleRectangularSimple2D( const TriangleRectangularSimple2D& value );
    virtual ~TriangleRectangularSimple2D( void );

    TriangleRectangularSimple2D& operator=( const TriangleRectangularSimple2D& rhv );

    void setOpposite( const double value );
    void setAdjacent( const double value );
    void setHypotenuse( const double value );

    const double getOpposite( void );
    const double getAdjacent( void );
    const double getHypotenuse( void );

    const double calculateOpposite( void );
    const double calculateAdjacent( void );
    const double calculateHypotenuse( void );

    const Angle& getAngle( void ) const;

protected:
private:
    void calculateQuarter( void );
    void calculateAngle( void );

    double m_opposite = 0.0;
    double m_adjacent = 0.0;
    double m_hypotenuse = 0.0;
    Angle m_angle;
    unsigned short m_quarter = 0;

};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( Math )
NAMESPACE_END( CUL )