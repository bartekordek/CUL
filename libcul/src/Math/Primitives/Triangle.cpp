#include "CUL/Math/Primitives/Triangle.hpp"

using namespace CUL;
using namespace MATH;
using namespace Primitives;

Triangle::Triangle()
{
    initializeData();
    updateData();
}

Triangle::Triangle( const Triangle& arg ) : ISerializable(), data( arg.data )
{
    initializeData();
    updateData();
}

Triangle::Triangle( const QuadData& dataIn )
{
    setData( dataIn );
}

void Triangle::initializeData()
{
    for( auto& point : data )
    {
        for( auto& value : point )
        {
            value = 0.f;
        }
    }
}

Triangle& Triangle::operator=( const Triangle& arg )
{
    if( this != &arg )
    {
        data = arg.data;
        updateData();
    }
    return *this;
}

Triangle& Triangle::operator=( const QuadData& dataIn )
{
    setData( dataIn );
    return *this;
}

void* Triangle::dataVoid()
{
    return dataAsVoid;
}

void Triangle::setData( const QuadData& dataIn )
{
    data = dataIn;
}

Triangle::PointType& Triangle::operator[]( size_t index )
{
    return data[index];
}

const Triangle::PointType& Triangle::operator[]( size_t index ) const
{
    return data[index];
}

void Triangle::updateData()
{
    auto convertedToVoid = reinterpret_cast<const void*>( &data );
    dataAsVoid = const_cast<void*>( convertedToVoid );
}

String Triangle::getSerializationContent( CounterType tabsSize, const bool ) const
{
    String tabs = getTab( tabsSize );

    auto convertPoint = []( const PointType& value )
    {
        return String( "{ " ) + String( value[0] ) + String( ", " ) + String( value[1] ) + String( ", " ) + String( value[2] ) +
               String( " }" );
    };

    String result;
    result = result + tabs + "    \"name\":\"Triangle\",\n";
    result = result + tabs + "    \"p1\": " + convertPoint( data[0] ) + ",\n";
    result = result + tabs + "    \"p2\": " + convertPoint( data[1] ) + ",\n";
    result = result + tabs + "    \"p3\": " + convertPoint( data[2] ) + ",\n";
    result = result + tabs + "    \"p4\": " + convertPoint( data[3] ) + "\n";

    return result;
}

std::vector<float> Triangle::toVectorOfFloat() const
{
    std::vector<float> result;

    for( const auto& row : data )
    {
        for( const auto& cell : row )
        {
            result.push_back( cell );
        }
    }

    return result;
}

size_t Triangle::getStride()
{
    return sizeof( PointType );
}

Triangle::~Triangle()
{
}