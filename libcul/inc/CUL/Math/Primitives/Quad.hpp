#pragma once

#include "CUL/ISerializable.hpp"
#include "CUL/Math/Vector3D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )
NAMESPACE_BEGIN( Primitives )

template <typename Type>
class Quad:
    public ISerializable
{
public:
    Quad()
    {

    }


    Quad( const Quad& arg ):
        p1( arg.p1 ),
        p2( arg.p2 ),
        p3( arg.p3 ),
        p4( arg.p4 )
    {
    }

    Quad& operator=( const Quad& arg )
    {
        if( this != &arg )
        {
            p1 = arg.p1;
            p2 = arg.p2;
            p3 = arg.p3;
            p4 = arg.p4;
        }
        return *this;
    }


    Vector3D<Type> p1;
    Vector3D<Type> p2;
    Vector3D<Type> p3;
    Vector3D<Type> p4;


    virtual ~Quad()
    {

    }
protected:
private:

    String getSerializationContent( CounterType tabsSize, const bool = false ) const override
    {
        String tabs = getTab( tabsSize );

        String result;
        result = result + tabs + "    \"name\":\"Quad\"\n";
        result = result + tabs + "    \"p1\":\n" + p1.serialize( tabsSize + 1, true );
        result = result + tabs + "    \"p2\":\n" + p2.serialize( tabsSize + 1, true );
        result = result + tabs + "    \"p3\":\n" + p3.serialize( tabsSize + 1, true );
        result = result + tabs + "    \"p4\":\n" + p4.serialize( tabsSize + 1 );

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