#include "CUL/Math/Primitives/Line.hpp"

using namespace CUL;
using namespace MATH;
using namespace Primitives;

Line::Line()
{
    data[0] = {{ 0.f, 0.f, 0.f }};
    data[1] = {{ 0.f, 0.f, 0.f }};
    updateData();
}

Line::Line( const Line& arg ):
    ISerializable(),
    data( arg.data )
{
    updateData();
}

Line& Line::operator=( const Line& arg )
{
    if( this != &arg )
    {
        data = arg.data;
        updateData();
    }
    return *this;
}

void* Line::dataVoid()
{
    return dataAsVoid;
}

void Line::setData( const LineData& dataIn )
{
    data = dataIn;
}

Line::PointType& Line::operator[]( size_t index )
{
    return data[ index ];
}

const Line::PointType& Line::operator[]( size_t index ) const
{
    return data[ index ];
}

void Line::updateData()
{
    auto convertedToVoid = reinterpret_cast<const void*>(&data);
    dataAsVoid = const_cast<void*>(convertedToVoid);
}

std::vector<float> Line::toVectorOfFloat() const
{
    std::vector<float> result;

    result.push_back( data[0][0] );
    result.push_back( data[0][1] );
    result.push_back( data[0][2] );

    result.push_back( data[1][0] );
    result.push_back( data[1][1] );
    result.push_back( data[1][2] );

    return result;
}

String Line::getSerializationContent( CounterType tabsSize, const bool ) const
{
    String tabs = getTab( tabsSize );

    auto convertPoint = []( const PointType& value ){
        return String( "{ " ) +
            String( value[0] ) +
            String( ", " ) +
            String( value[1] ) +
            String( ", " ) +
            String( value[2] ) +
            String( " }" );
    };

    String result;
    result = result + tabs + "    \"name\":\"Line\",\n";
    result = result + tabs + "    \"p1\": " + convertPoint( data[0] ) + ",\n";
    result = result + tabs + "    \"p2\": " + convertPoint( data[3] ) + "\n";

    return result;
}

Line::~Line()
{

}