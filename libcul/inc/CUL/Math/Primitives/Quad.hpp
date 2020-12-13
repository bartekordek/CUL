#pragma once

#include "CUL/ISerializable.hpp"
#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( Primitives )

struct SimplePos
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

template <typename Type>
class Quad:
    public ISerializable
{
public:
    using PointType = SimplePos;
    using DataType = std::array< PointType, 4 >;

    Quad()
    {

    }

    Quad( const Quad& arg ):
        data( arg.data )
    {
    }

    Quad& operator=( const Quad& arg )
    {
        if( this != &arg )
        {
            data = arg.data;
        }
        return *this;
    }

    const PointType& p1() const
    {
        return data[ 0 ];
    }

    const PointType& p2() const
    {
        return data[ 1 ];
    }

    const PointType& p3() const
    {
        return data[ 2 ];
    }

    const PointType& p4() const
    {
        return data[ 3 ];
    }

    PointType& p1()
    {
        return data[ 0 ];
    }

    PointType& p2()
    {
        return data[ 1 ];
    }

    PointType& p3()
    {
        return data[ 2 ];
    }

    PointType& p4()
    {
        return data[ 3 ];
    }


    DataType data;

    virtual ~Quad()
    {

    }
protected:
private:

    String getSerializationContent( CounterType tabsSize, const bool = false ) const override
    {
        String tabs = getTab( tabsSize );

        auto convertPoint = []( const PointType& value ){
            return String( "{ " ) +
                String( value.x ) +
                String( ", " ) + 
                String( value.y ) +
                String( ", " ) + 
                String( value.z ) +
                String( " }" );
        };

        String result;
        result = result + tabs + "    \"name\":\"Quad\"\n";
        result = result + tabs + "    \"p1\": " + convertPoint( data[0] );
        result = result + tabs + "    \"p2\": " + convertPoint( data[1] );
        result = result + tabs + "    \"p3\": " + convertPoint( data[2] );
        result = result + tabs + "    \"p4\": " + convertPoint( data[3] );

        return result;
    }

    // Deleted:
    Quad( Quad&& arg ) = delete;
    Quad& operator=( Quad&& arg ) = delete;
};

using QuadF = Quad<float>;
using QuadD = Quad<double>;
using QuadI = Quad<int>;
using QuadUi = Quad<unsigned int>;

NAMESPACE_END( Primitives )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )