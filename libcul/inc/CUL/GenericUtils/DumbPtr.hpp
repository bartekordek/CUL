#pragma once

#include "CUL/GenericUtils/LckPrim.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

template <class Type>
class CULLib_API DumbPtr
{
public:
    DumbPtr()
    {
    }

    DumbPtr( DumbPtr&& arg ):
        m_ptr( std::move( arg.m_ptr ) )
    {

    }

    DumbPtr( Type* value ):
        m_ptr( value )
    {
    }

    Type& operator*()
    {
        return *m_ptr;
    }

    Type* operator->()
    {
        return m_ptr;
    }

    const Type* operator->() const
    {
        return m_ptr;
    }

    DumbPtr<Type>& operator=( const Type* rhv )
    {
        m_ptr = const_cast<Type*>( rhv );
        m_destroyed = false;
        return *this;
    }

    DumbPtr<Type>& operator=( DumbPtr<Type>& arg )
    {
        m_ptr = std::move( arg.m_ptr );
        arg.m_destroyed = true;
        return *this;
    }

    DumbPtr<Type>& operator=( DumbPtr<Type>&& arg )
    {
        m_ptr = std::move( arg.m_ptr );
        arg.m_destroyed = true;
        return *this;
    }

    DumbPtr<Type>& operator=( Type* rhv )
    {
        Assert::simple( m_ptr == nullptr, "Trying to override pointer, previous pointer exists." );
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

    void reset( Type* value )
    {
        m_ptr = value;
    }

    Type* get()
    {
        return m_ptr;
    }

    operator Type*()
    {
        return m_ptr;
    }

    bool operator==( const DumbPtr<Type>& arg ) const
    {
        return *m_ptr == *arg.m_ptr;
    }

    bool operator<( const DumbPtr<Type>& arg ) const
    {
        return *m_ptr < *arg.m_ptr;
    }

    bool operator>( const DumbPtr<Type>& arg ) const
    {
        return *m_ptr > *arg.m_ptr;
    }

    virtual ~DumbPtr()
    {
        release();
    }

    void release()
    {
        delete m_ptr;
        m_ptr = nullptr;
    }

    bool isReleased()
    {
        return m_destroyed;
    }

private:
    DumbPtr( const DumbPtr& value ) = delete;
    DumbPtr& operator=( const DumbPtr& value ) = delete;

    Type* m_ptr = nullptr;
    LckBool m_destroyed = false;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )