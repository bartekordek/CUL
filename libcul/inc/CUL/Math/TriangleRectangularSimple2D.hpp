#pragma once

#include "CUL/Math/Angle.hpp"
#include "CUL/Math/Epsilon.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class CULLib_API TriangleRectangularSimple2D:
    public Epsilon<double>
{
public:
    TriangleRectangularSimple2D();
    TriangleRectangularSimple2D( const TriangleRectangularSimple2D& value );
    virtual ~TriangleRectangularSimple2D();

    TriangleRectangularSimple2D& operator=( const TriangleRectangularSimple2D& rhv );

    void setOpposite( const double value );
    void setAdjacent( const double value );
    void setHypotenuse( const double value );

    double getOpposite();
    double getAdjacent();
    double getHypotenuse();
    double calculateOpposite();
    double calculateAdjacent();
    double calculateHypotenuse();

    const Angle& getAngle() const;

protected:
private:
    void calculateQuarter();
    void calculateAngle();

    double m_opposite = 0.0;
    double m_adjacent = 0.0;
    double m_hypotenuse = 0.0;
    Angle m_angle;
    unsigned short m_quarter = 0;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )