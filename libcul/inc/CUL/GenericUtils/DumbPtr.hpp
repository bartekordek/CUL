#pragma once

#include "CUL/GenericUtils/SimpleAssert.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4710 )
#endif

template <class Type>
class DumbPtr
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
        return *this;
    }

    DumbPtr<Type>& operator=( DumbPtr<Type>& arg )
    {
        m_ptr = std::move( arg.m_ptr );
        return *this;
    }

    DumbPtr<Type>& operator=( DumbPtr<Type>&& arg )
    {
        m_ptr = std::move( arg.m_ptr );
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

    void set( Type* value )
    {
        if( value == nullptr )
        {
            release();
        }

        m_ptr = value;
    }

    void reset( Type* value )
    {
        if( value == nullptr )
        {
            release();
        }

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

    void setDeleter( std::function<void(void*)> deleter )
    {
        m_customDestuction = deleter;
    }

    virtual ~DumbPtr()
    {
        release();
    }

    void release()
    {
        if( isReleased() )
        {
            return;
        }

    if( m_customDestuction )
    {
        m_ptr->~Type();
        m_customDestuction( m_ptr );
    }
    else
    {
        delete m_ptr;
    }

        m_ptr = nullptr;
    }

    bool isReleased()
    {
        return m_ptr == nullptr;
    }

private:
    DumbPtr( const DumbPtr& value ) = delete;
    DumbPtr& operator=( const DumbPtr& value ) = delete;

    Type* m_ptr = nullptr;
    std::function<void(void*)> m_customDestuction;

};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )