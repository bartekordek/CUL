#include "CUL/Math/Primitives/Triangle.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( Primitives )

Triangle::Triangle()
{
}

Triangle::Triangle( const Triangle& arg ) : ISerializable(), vals( arg.vals )
{
}

Triangle& Triangle::operator=( const Triangle& arg )
{
    if( this != &arg )
    {
        vals = arg.vals;
    }
    return *this;
}

Triangle::PointType& Triangle::operator[]( size_t index )
{
    return vals[index];
}

const Triangle::PointType& Triangle::operator[]( size_t index ) const
{
    return vals[index];
}

std::vector<float> Triangle::toVectorOfFloat() const
{
    std::vector<float> result;

    for( size_t i = 0; i < 3; ++i )
    {
        result.push_back( vals[i].getX() );
        result.push_back( vals[i].getY() );
        result.push_back( vals[i].getZ() );
    }

    return result;
}

String Triangle::getSerializationContent( CounterType tabsSize, const bool ) const
{
    String tabs = getTab( tabsSize );

    auto convertPoint = []( const PointType& value ){
        return String( "{ " ) +
            String( value.getX() ) +
            String( ", " ) +
            String( value.getY() ) +
            String( ", " ) +
            String( value.getZ() ) +
            String( " }" );
    };

    String result;
    result = result + tabs + "    \"name\":\"Triangle\",\n";
    result = result + tabs + "    \"p1\": " + convertPoint( vals[0] ) + ",\n";
    result = result + tabs + "    \"p2\": " + convertPoint( vals[1] ) + ",\n";
    result = result + tabs + "    \"p3\": " + convertPoint( vals[2] ) + "\n";

    return result;
}

Triangle::~Triangle()
{
}

NAMESPACE_END( Primitives )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )