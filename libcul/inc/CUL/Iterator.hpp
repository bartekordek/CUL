#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )

template< typename T >
class Enum
{
public:
    class Iterator
    {
    public:
        Iterator( short value ):
            m_value( value )
        { }

        T operator*() const
        {
            return ( T ) m_value;
        }

        void operator++()
        {
            ++m_value;
        }

        bool operator!=( Iterator rhs )
        {
            return m_value != rhs.m_value;
        }

        const short value() const
        {
            return m_value;
        }

    private:
        short m_value;
    };

};

template< typename T >
typename Enum<T>::Iterator begin( Enum<T> )
{
    return typename Enum<T>::Iterator( ( short ) T::First );
}

template< typename T >
typename Enum<T>::Iterator end( Enum<T> )
{
    return typename Enum<T>::Iterator( ( ( short ) T::Last ) + 1 );
}

NAMESPACE_END( CUL )