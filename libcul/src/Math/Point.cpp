#include "CUL/Math/Point.hpp"

using namespace CUL;
using namespace MATH;

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 5045 )
#endif

Point::Point() noexcept
{

}

Point::Point( const glm::vec3& vec ) noexcept : values( { { vec.x, vec.y, vec.z } } )
{
    calculateDiagonal();
}

Point::Point(
    Point::Type inx,
    Point::Type iny, Point::Type inz ) noexcept :
    values( { { inx, iny, inz } } )
{
    calculateDiagonal();
}

Point::Point( const PointData& data ) noexcept :
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

Point& Point::operator=( const glm::vec3& vec )
{
    values[0] = vec.x;
    values[1] = vec.y;
    values[2] = vec.z;

    calculateDiagonal();
    return *this;
}

Point::operator glm::vec3()
{
    glm::vec3 result;
    result.x = values[0];
    result.y = values[1];
    result.z = values[2];
    return result;
}

Point::Point( const Point& arg ) noexcept :
    values( arg.values ),
    diagonal( arg.diagonal )
{
}

Point::Point( Point&& arg ) noexcept :
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

Point& Point::operator=( Point&& rhv ) noexcept
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

glm::vec3 Point::toGlmVec() const
{
    glm::vec3 result;
    result.x = values[0];
    result.y = values[1];
    result.z = values[2];
    return result;
}

Point::~Point()
{

}

#if _MSC_VER
#pragma warning( pop )
#endif