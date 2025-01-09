#pragma once

#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

using CounterType = unsigned;

class CULLib_API ISerializable
{
public:
    ISerializable();

    String serialize( CounterType tabsSize, const bool separator = false ) const;

    virtual ~ISerializable();
protected:

    static String getTab( CounterType tabsSize );

private:
    virtual String getSerializationContent( CounterType tabsSize, const bool separator = false ) const = 0;

    static CounterType s_spacesInTab;

    // Deleted:
    ISerializable( const ISerializable& arg ) = delete;
    ISerializable( ISerializable&& arg ) = delete;
    ISerializable& operator=( const ISerializable& arg ) = delete;
    ISerializable& operator=( ISerializable&& arg ) = delete;
};

NAMESPACE_END( CUL )