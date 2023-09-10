#pragma once

#include "CUL/CUL.hpp"

NAMESPACE_BEGIN( CUL )

template<class Type>
class Singleton
{
public:
    static Type& getInstance()
    {
        static Type instance;
        return instance;
    }

    Singleton() = default;
    virtual ~Singleton() = default;
    Singleton( const Singleton& ) = delete;
    Singleton( Singleton&& ) = delete;
    Singleton& operator=( const Singleton& ) = delete;
    Singleton& operator=( Singleton&& ) = delete;

protected:
private:
};

NAMESPACE_END( CUL )