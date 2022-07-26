#pragma once

#include "CUL/Memory/MemoryPool.hpp"

#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_utility.hpp"

NAMESPACE_BEGIN( CUL::Memory )
template <class Type, size_t Size>
class UniquePtrOnStack
{
public:
    UniquePtrOnStack()
    {
    }

    UniquePtrOnStack( std::function<void*( void )> inCreator, std::function<void*( void )> inDestructor ) : m_destructor( inDestructor )
    {
        m_ptr = inCreator( m_memoryPool.getMemory( m_pointerSize ) );
    }

    explicit UniquePtrOnStack( std::function<Type*( void* )> creationFunction )
    {
        void* memory = m_memoryPool.getMemory( m_pointerSize );
        m_ptr = creationFunction( memory );
    }

    explicit UniquePtrOnStack( Type* ptr ) : m_ptr( ptr )
    {
    }

    void create( std::function<Type*( void* )> inCreator, std::function<void( Type* ptr )> inDestructor )
    {
        m_destructor = inDestructor;
        m_ptr = inCreator( m_memoryPool.getMemory( m_pointerSize ) );
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

    UniquePtrOnStack<Type, Size>& operator=( const Type* rhv )
    {
        m_ptr = const_cast<Type*>( rhv );
        return *this;
    }

    UniquePtrOnStack<Type, Size>& operator=( Type* rhv ) = delete;

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
        if( value == nullptr )
        {
            release();
        }

        m_ptr = value;
    }

    /*
    UniquePtrOnStack<Type, Size>& operator=( UniquePtrOnStack<Type, Size>&& value )
    {
        if( this != &value )
        {
            m_ptr = value.m_ptr;
            value.m_ptr = nullptr;
            m_memoryPool = std::move( value.m_memoryPool );
        }
        return *this;
    }
    */

    Type* get()
    {
        return m_ptr;
    }

    explicit operator Type*()
    {
        return m_ptr;
    }

    bool operator==( const UniquePtrOnStack<Type, Size>& arg ) const
    {
        return *m_ptr == *arg.m_ptr;
    }

    bool operator<( const UniquePtrOnStack<Type, Size>& arg ) const
    {
        return *m_ptr < *arg.m_ptr;
    }

    bool operator>( const UniquePtrOnStack<Type, Size>& arg ) const
    {
        return *m_ptr > *arg.m_ptr;
    }

    virtual ~UniquePtrOnStack()
    {
        release();
    }

    void release()
    {
        if( isReleased() )
        {
            return;
        }

        if( m_destructor )
        {
            m_destructor( m_ptr );
        }

        m_memoryPool.release( m_ptr );
        m_ptr = nullptr;
    }

    bool isReleased()
    {
        return m_ptr == nullptr;
    }

protected:
private:
    std::function<void( Type* ptr )> m_destructor;

    size_t m_pointerSize = Size;
    MemoryPool<Size> m_memoryPool;
    Type* m_ptr = nullptr;

    UniquePtrOnStack& operator=( const UniquePtrOnStack& value ) = delete;
    UniquePtrOnStack& operator=( UniquePtrOnStack&& value ) = delete;
    UniquePtrOnStack( const UniquePtrOnStack& value ) = delete;
    UniquePtrOnStack( UniquePtrOnStack&& value ) = delete;
};

NAMESPACE_END( CUL::Memory )