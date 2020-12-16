#pragma once

#include "CUL/ISerializable.hpp"
#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( Primitives )

template <typename Type>
class Triangle:
    public ISerializable
{
public:
    using PointType = Vector3D<Type>;
    using ValuesType = std::array< PointType, 3 >;

    ValuesType vals;

    Triangle()
    {

    }

    Triangle( const Triangle& arg ):
        vals( arg.vals )
    {

    }

    Triangle& operator=( const Triangle& arg )
    {
        if( this != &arg )
        {
            vals = arg.vals;
        }
        return *this;
    }

    const PointType& p1() const
    {
        return vals[ 0 ];
    }

    const PointType& p2() const
    {
        return vals[ 1 ];
    }

    const PointType& p3() const
    {
        return vals[ 2 ];
    }

    const PointType& p4() const
    {
        return vals[ 3 ];
    }

    PointType& p1()
    {
        return vals[ 0 ];
    }

    PointType& p2()
    {
        return vals[ 1 ];
    }

    PointType& p3()
    {
        return vals[ 2 ];
    }

    virtual ~Triangle()
    {

    }

protected:
private:
    String getSerializationContent( CounterType tabsSize, const bool = false ) const override
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

    // Deleted:
    Triangle( Triangle&& arg ) = delete;
    Triangle& operator=( Triangle&& arg ) = delete;
};

using TriangleF = Triangle<float>;
using TriangleD = Triangle<double>;
using TriangleI = Triangle<int>;
using TriangleU = Triangle<unsigned int>;

NAMESPACE_END( Primitives )
NAMESPACE_END( MATH )
NAMESPACE_END( CUL )