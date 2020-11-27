#pragma once

#include "CUL/GenericUtils/IOnChange.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

template<typename Type>
class CULLib_API ValueChangeHook:
    public IOnChange
{
public:

    ValueChangeHook()
    {

    }

    ValueChangeHook( const ValueChangeHook& arg ):
        m_value( arg.m_value ),
        m_oldValue( arg.m_oldValue )
    {

    }


    ValueChangeHook( const Type& value ):
        m_value( value )
    {

    }

    ValueChangeHook& operator=( const Type& arg )
    {
        if( m_value != arg )
        {
            m_value = arg;
            IOnChange::onChange();
        }

        return m_value;
    }

    ValueChangeHook& operator=( const ValueChangeHook& arg )
    {
        if( this != &arg )
        {
            m_value = arg.m_value;
        }
        return this;
    }

    operator Type() const
    {
        return m_value;
    }

    operator Type& ()
    {
        return m_value;
    }

    Type& getRef()
    {
        return m_value;
    }

    void runIfChanged()
    {
        if( m_oldValue != m_value )
        {
            IOnChange::onChange();
            m_oldValue = m_value;
        }
    }

    virtual ~ValueChangeHook()
    {

    }
protected:
private:
    Type m_value;
    Type m_oldValue;

    // Deleted:
    ValueChangeHook( ValueChangeHook&& arg ) = delete;
    ValueChangeHook& operator=( ValueChangeHook&& arg ) = delete;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )