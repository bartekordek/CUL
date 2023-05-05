#include "CUL/Math/Primitives/Quad.hpp"

using namespace CUL;
using namespace MATH;
using namespace Primitives;

Quad::Quad()
{
    initializeData();
    updateData();
}

Quad::Quad( const Quad& arg ) : ISerializable(), data( arg.data )
{
    initializeData();
    updateData();
}

Quad::Quad( const QuadData& dataIn )
{
    setData( dataIn );
}

void Quad::initializeData()
{
    for( auto& point: data )
    {
        for( auto& value: point )
        {
            value = 0.f;
        }
    }
}

Quad& Quad::operator=( const Quad& arg )
{
    if( this != &arg )
    {
        data = arg.data;
        updateData();
    }
    return *this;
}


Quad& Quad::operator=(const QuadData& dataIn)
{
    setData(dataIn);
    return *this;
}

void* Quad::dataVoid()
{
    return dataAsVoid;
}

void Quad::setData( const QuadData& dataIn )
{
    data = dataIn;
}

Quad::PointType& Quad::operator[]( size_t index )
{
    return data[index];
}

const Quad::PointType& Quad::operator[]( size_t index ) const
{
    return data[index];
}

void Quad::updateData()
{
    auto convertedToVoid = reinterpret_cast<const void*>( &data );
    dataAsVoid = const_cast<void*>( convertedToVoid );
}

String Quad::getSerializationContent( CounterType tabsSize, const bool ) const
{
    String tabs = getTab( tabsSize );

    auto convertPoint = []( const PointType& value )
    {
        return String( "{ " ) + String( value[0] ) + String( ", " ) + String( value[1] ) + String( ", " ) + String( value[2] ) +
               String( " }" );
    };

    String result;
    result = result + tabs + "    \"name\":\"Quad\",\n";
    result = result + tabs + "    \"p1\": " + convertPoint( data[0] ) + ",\n";
    result = result + tabs + "    \"p2\": " + convertPoint( data[1] ) + ",\n";
    result = result + tabs + "    \"p3\": " + convertPoint( data[2] ) + ",\n";
    result = result + tabs + "    \"p4\": " + convertPoint( data[3] ) + "\n";

    return result;
}

std::vector<float> Quad::toVectorOfFloat() const
{
    std::vector<float> result;


    for (const auto& row: data)
    {
        for( const auto& cell : row )
        {
            result.push_back( cell );
        }
    }

    return result;
}

size_t Quad::getStride()
{
    return sizeof( PointType );
}

Quad::~Quad()
{
}