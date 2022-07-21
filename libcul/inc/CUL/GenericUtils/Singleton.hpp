#pragma once

#include "CUL/CUL.hpp"

NAMESPACE_BEGIN( CUL )

template<class Type>
class Singleton
{
public:
    Type& getInstance()
    {
        static Type instance;
        return instance;
    }
protected:
private:
    Singleton = default;
    ~Singleton = default;
    Singleton(const Singleton& arg) = delete;
    Singleton(Singleton&& arg) = delete;
    Singleton& operator=(const Singleton& rhv) = delete;
    Singleton& operator=(Singleton&& rhv) = delete;
};

NAMESPACE_END( CUL )