#pragma once

#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

template <class Type>
class CULLib_API DumbPtr
{
public:
    DumbPtr()
    {

    }

    DumbPtr( Type* value ):
        m_ptr( value )
    {

    }

    virtual ~DumbPtr()
    {
        delete m_ptr;
        m_ptr = nullptr;
    }

    Type& operator*()
    {
        return *m_ptr;
    }

    Type* operator->()
    {
        return m_ptr;
    }

    const Type* operator->()const
    {
        return m_ptr;
    }

    DumbPtr<Type>& operator=( const Type* rhv )
    {
        this->m_ptr = const_cast<Type*>( rhv );
        return *this;
    }

    DumbPtr<Type>& operator=( Type* rhv )
    {
        m_ptr = rhv;
        return *this;
    }

    const Type& operator*() const
    {
        return *m_ptr;
    }

    const Type* get() const
    {
        return m_ptr;
    }

    Type* get()
    {
        return m_ptr;
    }

    operator Type*()
    {
        return m_ptr;
    }

private:
    DumbPtr( const DumbPtr& value ) = delete;
    DumbPtr& operator=( const DumbPtr& value ) = delete;

    Type* m_ptr = nullptr;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )