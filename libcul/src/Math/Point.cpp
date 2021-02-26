#include "CUL/Math/Point.hpp"

using namespace CUL;
using namespace MATH;

Point::Point()
{

}

Point::Point(
    Point::Type inx,
    Point::Type iny,
    Point::Type inz ):
    values( { inx, iny, inz } )
{
    calculateDiagonal();
}

Point::Point( const PointData& data ):
    values( data )
{
}

Point& Point::operator=( const PointData& data )
{
    if( &this->values != &data )
    {
        values = data;
    }
    return *this;
}

Point::Point( const Point& arg ):
    values( arg.values ),
    diagonal( arg.diagonal )
{
}

Point::Point( Point&& arg ):
    values( std::move( arg.values ) ),
    diagonal( arg.diagonal )
{

}

Point& Point::operator=( const Point& rhv )
{
    if( this != &rhv )
    {
        values = rhv.values;
        diagonal = rhv.diagonal;
    }
    return *this;
}

Point& Point::operator=( Point&& rhv )
{
    if( this != &rhv )
    {
        values = std::move( rhv.values );
        diagonal = rhv.diagonal;
    }
    return *this;
}

Point& Point::operator+=( const Point& rhv )
{
    if( this != &rhv )
    {
        for( size_t i = 0; i < values.size(); ++i )
        {
            values[i] += rhv.values[i];
        }
        diagonal = rhv.diagonal;
    }
    return *this;
}

Point Point::operator+( const Point& rhv )
{
    Point result = *this;
    result += rhv;
    result.calculateDiagonal();
    return result;
}

Point& Point::operator-=( const Point& rhv )
{
    if( this != &rhv )
    {
        for( size_t i = 0; i < values.size(); ++i )
        {
            values[i] -= rhv.values[i];
        }
        calculateDiagonal();
    }
    return *this;
}

Point Point::operator-( const Point& rhv )
{
    Point result = *this;
    result -= rhv;
    result.calculateDiagonal();
    return result;
}

bool Point::operator<( const Point& rhv ) const
{
    return diagonal < rhv.diagonal;
}

Point::Type& Point::getValue( const AxisCarthesian axis )
{
    return values[static_cast<size_t>( axis )];
}

void Point::setAxisValue( AxisCarthesian axis, Point::Type value )
{
    values[static_cast<size_t>( axis )] = value;
    calculateDiagonal();
}

void Point::calculateDiagonal()
{
    diagonal = static_cast<Type>( std::sqrt( values[0] * values[0] + values[1] * values[1] + values[2] * values[2] ) );
}

Point::Type Point::operator[]( size_t index ) const
{
    return values[ index ];
}

Point::Type& Point::operator[]( size_t index )
{
    return values[ index ];
}

Point::~Point()
{

}