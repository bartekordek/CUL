#pragma once

#include "CUL/Math/Axis.hpp"
#include "CUL/Math/Math.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

template <typename Type>
class Point final
{
public:
    Type x = static_cast<Type>( 0 );
    Type y = static_cast<Type>( 0 );
    Type z = static_cast<Type>( 0 );
    Type diagonal = static_cast<Type>( 0 );

    const Type getX() const
    {
        return x;
    }

    const Type getY() const
    {
        return y;
    }

    const Type getZ() const
    {
        return z;
    }

    Point()
    {

    }

    Point(
        const Type& val1,
        const Type& val2,
        const Type& val3 ):
        x( val1 ),
        y( val2 ),
        z( val3 )
    {
        calculateDiagonal();
    }

    Point( const Point& arg ):
        x( arg.x ),
        y( arg.y ),
        z( arg.z ),
        diagonal( arg.diagonal )
    {
    }

    Point( Point&& arg ):
        x( arg.x ),
        y( arg.y ),
        z( arg.z ),
        diagonal( arg.diagonal )
    {

    }

    Point& operator=( const Point& rhv )
    {
        if( this != &rhv )
        {
            x = rhv.x;
            y = rhv.y;
            z = rhv.z;
            diagonal = rhv.diagonal;
        }
        return *this;
    }

    Point& operator=( Point&& rhv )
    {
        if( this != &rhv )
        {
            x = rhv.x;
            y = rhv.y;
            z = rhv.z;
            diagonal = rhv.diagonal;
        }
        return *this;
    }

    Point& operator+=( const Point& rhv )
    {
        if( this != &rhv )
        {
            x += rhv.x;
            y += rhv.y;
            z += rhv.z;
            diagonal = rhv.diagonal;
        }
        return *this;
    }

    Point<Type> operator+( const Point& rhv )
    {
        Point result;
        result.x += rhv.x;
        result.y += rhv.y;
        result.z += rhv.z;
        diagonal = rhv.diagonal;
        return result;
    }

    Point<Type>& operator-=( const Point& rhv )
    {
        if( this != &rhv )
        {
            x -= rhv.x;
            y -= rhv.y;
            z -= rhv.z;
            diagonal = rhv.diagonal;
        }
        return *this;
    }

    Point operator-( const Point& rhv )
    {
        Point result;
        result.x -= rhv.x;
        result.y -= rhv.y;
        result.z -= rhv.z;
        result.diagonal = rhv.diagonal;
        return result;
    }

    const bool operator<( const Point& rhv ) const
    {
        return diagonal < rhv.diagonal;
    }

    const Type& getValue( const AxisCarthesian axis )
    {
        if( AxisCarthesian::X == axis )
        {
            return x;
        }
        else if( AxisCarthesian::Y == axis )
        {
            return y;
        }
        else
        {
            return z;
        }
    }

    void setAxisValue( const AxisCarthesian axis, const Type& value )
    {
        if( AxisCarthesian::X == axis )
        {
            x = value;
        }
        else if( AxisCarthesian::Y == axis )
        {
            y = value;
        }
        else if( AxisCarthesian::Z == axis )
        {
            z = value;
        }
        calculateDiagonal();
    }

    void calculateDiagonal()
    {
        diagonal = static_cast<Type>( std::sqrt( x * x + y * y + z * z ) );
    }

    ~Point()
    {

    }
protected:
private:
};


using PointF = Point<float>;
using PointD = Point<double>;
using PointI = Point<int>;

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )