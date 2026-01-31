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

StringWr Quad::getSerializationContent( CounterType tabsSize, const bool ) const
{
    StringWr tabs = getTab( tabsSize );

    auto convertPoint = []( const PointType& value )
    {
        return String( "{ " ) + String( value[0] ) + String( ", " ) + String( value[1] ) + String( ", " ) + String( value[2] ) +
               String( " }" );
    };

    const StringWr result = StringWr::createFromPrintf( "Name: Quad\np1: %s\n, p2: %s\n, p3: %s\n, p4: %s",
        convertPoint( data[0] ).getUtfChar(),
        convertPoint( data[1] ).getUtfChar(),
        convertPoint( data[2] ).getUtfChar(),
        convertPoint( data[3] ).getUtfChar() );

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