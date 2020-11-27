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
    Vector3D<Type> p1;
    Vector3D<Type> p2;
    Vector3D<Type> p3;

    Triangle()
    {

    }

    Triangle( const Triangle& arg ):
        p1( arg.p1 ),
        p2( arg.p2 ),
        p3( arg.p3 )
    {

    }

    Triangle& operator=( const Triangle& arg )
    {
        if( this != &arg )
        {
            p1 = arg.p1;
            p2 = arg.p2;
            p3 = arg.p3;
        }
        return *this;
    }

    virtual ~Triangle()
    {

    }

protected:
private:
    String getSerializationContent( CounterType tabsSize, const bool = false ) const override
    {
        String tabs = getTab( tabsSize );

        String result;
        result = result + tabs + "    \"name\":\"Triangle\"\n";
        result = result + tabs + "    \"p1\":\n" + p1.serialize( tabsSize + 1, true );
        result = result + tabs + "    \"p2\":\n" + p2.serialize( tabsSize + 1, true );
        result = result + tabs + "    \"p3\":\n" + p3.serialize( tabsSize + 1 );

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