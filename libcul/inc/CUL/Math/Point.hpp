#pragma once

#include "CUL/Math/Axis.hpp"
#include "CUL/Math/Math.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

class CULLib_API Point final
{
public:
    using Type = float;
    using PointData = std::array<Type, 3>;

    PointData values;

    Type diagonal = 0.f;

    Point();
    Point( Type val1, Type val2, Type val3 );
    Point( const PointData& data );

    Point& operator=( const PointData& data );

    inline Type x() const
    {
        return values[0];
    }

    inline Type& x()
    {
        return values[0];
    }

    inline Type y() const
    {
        return values[1];
    }

    inline Type& y()
    {
        return values[1];
    }

    inline Type z() const
    {
        return values[2];
    }

    inline Type& z()
    {
        return values[2];
    }

    Point( const Point& arg );
    Point( Point&& arg );
    Point& operator=( const Point& rhv );
    Point& operator=( Point&& rhv );
    Point& operator+=( const Point& rhv );
    Point operator+( const Point& rhv );
    Point& operator-=( const Point& rhv );
    Point operator-( const Point& rhv );
    bool operator<( const Point& rhv ) const;

    Type& getValue( const AxisCarthesian axis );
    void setAxisValue( AxisCarthesian axis, Type value );

    Type operator[]( size_t index ) const;
    Type& operator[]( size_t index );

    ~Point();
protected:
private:
    void calculateDiagonal();
};
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )