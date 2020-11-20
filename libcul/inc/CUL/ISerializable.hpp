#pragma once

#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API ISerializable
{
public:
    ISerializable();

    virtual const String serialize() const = 0;

    virtual ~ISerializable();
protected:
private:

    // Deleted:
    ISerializable( const ISerializable& arg ) = delete;
    ISerializable( ISerializable&& arg ) = delete;
    ISerializable& operator=( const ISerializable& arg ) = delete;
    ISerializable& operator=( ISerializable&& arg ) = delete;
};

NAMESPACE_END( CUL )