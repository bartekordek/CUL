#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

template <typename Type>
class CULLib_API Pos2D
{
public:
    Pos2D()
    {

    }

    Pos2D(const Pos2D& val):
        m_x( val.m_x ),
        m_y( val.m_y )
    {

    }

    Pos2D(const Type x, const Type y):
        m_x( x ),
        m_y( y )
    {

    }

    virtual ~Pos2D()
    {

    }

    Pos2D& operator=(const Pos2D& rhv)
    {
        if( this != &rhv )
        {
            m_x = rhv.m_x;
            m_y = rhv.m_y;
        }
        return *this;
    }

    const Type getX(void)const
    {
        return m_x;
    }

    const Type getY(void)const
    {
        return m_y;
    }

    void setX(const Type val)
    {
        m_x = val;
    }

    void setY(const Type val)
    {
        m_y = val;
    }

    void setXY(const Type x, const Type y)
    {
        m_x = x;
        m_y = y;
    }

protected:
private:
    Type m_x = static_cast< Type >( 0 );
    Type m_y = static_cast< Type >( 0 );

};

using Pos2Di = Pos2D<int>;
using Pos2Dsi = Pos2D<short int>;

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )