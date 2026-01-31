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

StringWr Triangle::getSerializationContent( CounterType tabsSize, const bool ) const
{
    StringWr tabs = getTab( tabsSize );

    auto convertPoint = []( const PointType& value )
    {
        return String( "{ " ) + String( value[0] ) + String( ", " ) + String( value[1] ) + String( ", " ) + String( value[2] ) +
               String( " }" );
    };

    const StringWr result = StringWr::createFromPrintf( "Name: Triangle\np1: %s\n, p2: %s\n, p3: %s\n, p4: %s",
        convertPoint( data[0] ).getUtfChar(),
        convertPoint( data[1] ).getUtfChar(),
        convertPoint( data[2] ).getUtfChar(),
        convertPoint( data[3] ).getUtfChar() );
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