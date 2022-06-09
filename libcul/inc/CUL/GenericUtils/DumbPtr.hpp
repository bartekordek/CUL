#pragma once

#include "CUL/GenericUtils/LckPrim.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Memory/MemoryPool.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

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

    void setMemoryPool( Memory::MemoryPool* mp )
    {
        s_memoryPool = mp;
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

    void set( Type* value, Memory::MemoryPool* mp = nullptr )
    {
        if( value == nullptr )
        {
            release();
        }

        m_ptr = value;
        s_memoryPool = mp;
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

        if( s_memoryPool )
        {
            m_ptr->~Type();
            s_memoryPool->release( m_ptr );
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

    static void registerMemoryPool( Memory::MemoryPool* memoryPool )
    {
        s_memoryPool = memoryPool;
    }

private:
    DumbPtr( const DumbPtr& value ) = delete;
    DumbPtr& operator=( const DumbPtr& value ) = delete;

    Type* m_ptr = nullptr;

    static Memory::MemoryPool* s_memoryPool;
};

template <class Type>
Memory::MemoryPool* DumbPtr<Type>::s_memoryPool = nullptr;

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )