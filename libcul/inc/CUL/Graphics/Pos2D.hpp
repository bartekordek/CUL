#pragma once

#include "CUL/ISerializable.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
class CULLib_API Pos2D:
    public ISerializable
{
public:
    Pos2D()
    {
    }

    Pos2D( const Pos2D& val ):
        ISerializable(),
        m_x( val.m_x ),
        m_y( val.m_y )
    {
    }

    Pos2D( const Type x, const Type y ):
        m_x( x ),
        m_y( y )
    {
    }

    Pos2D& operator=( const Pos2D& rhv )
    {
        if( this != &rhv )
        {
            m_x = rhv.m_x;
            m_y = rhv.m_y;
        }
        return *this;
    }

    // TODO: write some comparators.
    bool operator==( const Pos2D& arg ) const
    {
        if( this == &arg )
        {
            return true;
        }

        return m_x == arg.m_x && m_y == arg.m_y;
    }

    const Type getX() const
    {
        return m_x;
    }

    const Type getY() const
    {
        return m_y;
    }

    void setX( const Type val )
    {
        m_x = val;
    }

    void setY( const Type val )
    {
        m_y = val;
    }

    void setXY( const Type x, const Type y )
    {
        m_x = x;
        m_y = y;
    }

    String getSerializationContent( CounterType tabsSize, const bool = false ) const override
    {
        String tabs = getTab( tabsSize );

        String result;
        result = result + tabs + "    \"x\": " + String( m_x ) + ",\n";
        result = result + tabs + "    \"y\": " + String( m_y ) + "\n";


        return result;
    }

    virtual ~Pos2D()
    {
    }

protected:
private:
    Type m_x = static_cast<Type>( 0 );
    Type m_y = static_cast<Type>( 0 );
};

using Pos2Di = Pos2D<int>;
using Pos2Dsi = Pos2D<short int>;

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )