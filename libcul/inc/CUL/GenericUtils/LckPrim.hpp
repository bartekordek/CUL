#pragma once
#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4251 )
#pragma warning( disable: 4820 )
#endif

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

template <typename Type>
class CULLib_API LckPrim
{
public:
    LckPrim()
    {
    }

    LckPrim( const Type& val )
    {
        std::lock_guard<std::mutex> lock( mtx );
        value = val;
    }

    LckPrim( const LckPrim<Type>& rvalue )
    {
        std::lock_guard<std::mutex> lock( mtx );
        value = rvalue.value;
    }

    virtual ~LckPrim()
    {
    }

    const Type& getVal() const
    {
        std::lock_guard<std::mutex> lock( mtx );
        return value;
    }

    const Type getValCopy() const
    {
        return value;
    }

    void setVal( const Type& val )
    {
        std::lock_guard<std::mutex> lock( mtx );
        value = val;
    }

    Type& operator++()
    {
        std::lock_guard<std::mutex> lock( mtx );
        ++value;
        return value;
    }

    Type operator++( int )
    {
        std::lock_guard<std::mutex> lock( mtx );
        Type copy = value;
        ++value;
        return copy;
    }

    Type& operator--()
    {
        std::lock_guard<std::mutex> lock( mtx );
        --value;
        return value;
    }

    Type operator--( int )
    {
        std::lock_guard<std::mutex> lock( mtx );
        Type copy = value;
        --value;
        return copy;
    }

    bool operator==( const LckPrim<Type>& val )
    {
        std::lock_guard<std::mutex> lock( mtx );
        return value == val.value;
    }

    bool operator==( const Type& val )
    {
        std::lock_guard<std::mutex> lock( mtx );
        return value == val;
    }

    operator Type()
    {
        return value;
    }

    LckPrim<Type>& operator=( const LckPrim<Type>& rvalue )
    {
        if( this != &rvalue )
        {
            std::lock_guard<std::mutex> lock( mtx );
            value = rvalue.value;
        }
        return *this;
    }

    LckPrim<Type>& operator=( const Type& right )
    {
        std::lock_guard<std::mutex> lock( mtx );
        value = right;
        return *this;
    }

protected:
private:
    std::mutex mtx;
    Type value = static_cast<Type>( 0 );
};

template <typename Type>
bool operator==( const Type& r, LckPrim<Type>&l )
{
    return l == r;
}

using LckBool = LckPrim<bool>;

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )

#if _MSC_VER
__pragma( warning( pop ) )
#endif