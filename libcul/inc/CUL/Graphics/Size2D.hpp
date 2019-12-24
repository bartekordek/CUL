#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
class CULLib_API Size2D
{
public:
    Size2D()
    {

    }

    Size2D( const Size2D& s2 ):
        m_width( s2.m_width ),
        m_height( s2.m_height )
    {

    }

    Size2D( const Type width, const Type height ):
        m_width( width ),
        m_height( height )
    {

    }

    virtual ~Size2D()
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

protected:
private:
    Type m_width = static_cast< Type >( 0 );
    Type m_height = static_cast< Type >( 0 );

};

using Size2Du = Size2D<unsigned>;
using Size2Dsu = Size2D<unsigned short int>;

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )