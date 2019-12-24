#pragma once

#include "CUL/Math/Epsilon.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

template <typename Type>
class PosTable:
    public Epsilon<Type>
{
public:
    PosTable()
    {

    }

    template <class SomeOtherClass>
    PosTable( const Type& row, const Type& col ):
        m_row( row ),
        m_col( col )
    {

    }

    PosTable( const PosTable<Type>& table ):
        m_row( table.m_row ),
        m_col( table.m_col )
    {

    }

    virtual ~PosTable() = default;

    template <class SomeOtherClass>
    PosTable( const PosTable<SomeOtherClass>& table ):
        m_row( static_cast<Type>( table.m_row ) ),
        m_col( static_cast<Type>( table.m_col ) )
    {

    }

    const Type getRow() const
    {
        return m_row;
    }

    const Type getCol() const
    {
        return m_col;
    }

    void setRow( const Type row )
    {
        m_row = row;
    }

    void setCol( const Type col )
    {
        m_col = col;
    }

    void setBoth( const Type& row, const Type& col )
    {
        m_row = row;
        m_col = col;
    }

    const bool operator==( const PosTable<Type>& rhv ) const
    {
        if( &rhv != this )
        {
            if( false == Epsilon<Type>::equals( m_row, rhv.m_row ) ||
                false == Epsilon<Type>::equals( m_col, rhv.m_col ) )
            {
                return false;
            }
        }
        return true;
    }

    PosTable<Type>& operator=( const PosTable<Type>& rhv )
    {
        if( &rhv != this )
        {
            m_row = rhv.m_row;
            m_col = rhv.m_col;
        }
        return *this;
    }

    PosTable<Type> operator*( const PosTable<Type>& rhv ) const = delete;
    PosTable<Type> operator/( const PosTable<Type>& rhv ) const = delete;
    PosTable<Type>& operator*=( const PosTable<Type>& rhv ) = delete;
    PosTable<Type>& operator/=( const PosTable<Type>& rhv ) = delete;

    PosTable<Type>& operator+=( const PosTable<Type>& rhv )
    {
        m_row += rhv.m_row;
        m_col += rhv.m_col;
        return *this;
    }

    PosTable<Type> operator+( const PosTable<Type>& rhv ) const
    {
        PosTable<Type> result( *this );
        result += rhv;
        return result;
    }

    PosTable<Type>& operator-=( const PosTable<Type>& rhv )
    {
        m_row -= rhv.m_row;
        m_col -= rhv.m_col;
        return *this;
    }

    PosTable<Type> operator-( const PosTable<Type>& rhv ) const
    {
        PosTable<Type> result( *this );
        result -= rhv;
        return result;
    }

protected:
private:
    Type m_row = static_cast<Type>( 0 );
    Type m_col = static_cast<Type>( 0 );
};

using PosTableU = PosTable<unsigned>;
using PosTableI = PosTable<int>;


NAMESPACE_END( Math )
NAMESPACE_END( CUL )