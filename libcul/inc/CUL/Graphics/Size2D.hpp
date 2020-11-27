#pragma once

#include "CUL/ISerializable.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
class CULLib_API Size2D:
    public CUL::ISerializable
{
public:
    Size2D()
    {
    }

    Size2D( const Size2D& s2 ):
        CUL::ISerializable(),
        m_width( s2.m_width ),
        m_height( s2.m_height )
    {
    }

    Size2D( const Type width, const Type height ):
        m_width( width ),
        m_height( height )
    {
    }

    Size2D& operator=( const Size2D& rhv )
    {
        if( this != &rhv )
        {
            m_width = rhv.m_width;
            m_height = rhv.m_height;
        }
        return *this;
    }

    bool operator==( const Size2D& arg ) const
    {
        if( this == &arg )
        {
            return true;
        }
        return m_width == arg.m_width && m_height == arg.m_height;
    }

    void setWidth( const Type width )
    {
        m_width = width;
    }

    void setHeight( const Type height )
    {
        m_height = height;
    }

    void setSize( const Type width, const Type height )
    {
        m_width = width;
        m_height = height;
    }

    const Type getWidth() const
    {
        return m_width;
    }

    const Type getHeight() const
    {
        return m_height;
    }

    const Type getRatio() const
    {
        return m_width / m_height;
    }

    String getSerializationContent( CounterType tabsSize, const bool = false ) const override
    {
        String tabs = getTab( tabsSize );

        String result;
        result = result + tabs + "    \"width\": " + String( m_width ) + ",\n";
        result = result + tabs + "    \"height\": " + String( m_height ) + "\n";

        return result;
    }

    virtual ~Size2D()
    {
    }

protected:
private:
    Type m_width = static_cast<Type>( 0 );
    Type m_height = static_cast<Type>( 0 );
};

using Size2Du = Size2D<unsigned>;
using Size2Di = Size2D<int>;
using Size2Dsu = Size2D<unsigned short int>;

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )
