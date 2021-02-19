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
        updateData();
    }

    Quad( const Quad& arg ):
        ISerializable(),
        data( arg.data )
    {
        updateData();
    }

    Quad& operator=( const Quad& arg )
    {
        if( this != &arg )
        {
            data = arg.data;
            updateData();
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

    void* dataVoid()
    {
        return dataAsVoid;
    }

    void setData( const std::array< std::array<Type, 3>, 4 >& dataIn )
    {
        auto setPoint = []( PointType& point, const std::array<Type, 3>& rhv ){
            point.x = rhv[0];
            point.y = rhv[1];
            point.z = rhv[2];
        };

        for( size_t i = 0; i < data.size(); ++i )
        {
            setPoint( data[i], dataIn[i] );
        }
    }


    DataType data;
    void* dataAsVoid = nullptr;

    virtual ~Quad()
    {

    }
protected:
private:
    void updateData()
    {
        auto convertedToVoid = reinterpret_cast<const void*>(&data);
        dataAsVoid = const_cast<void*>(convertedToVoid);
    }

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
        result = result + tabs + "    \"name\":\"Quad\",\n";
        result = result + tabs + "    \"p1\": " + convertPoint( data[0] ) + ",\n";
        result = result + tabs + "    \"p2\": " + convertPoint( data[1] ) + ",\n";
        result = result + tabs + "    \"p3\": " + convertPoint( data[2] ) + ",\n";
        result = result + tabs + "    \"p4\": " + convertPoint( data[3] ) + "\n";

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