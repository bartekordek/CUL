#pragma once

#include "CUL/Graphics/IObject.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class CULLib_API IObjectRegister
{
public:
    IObjectRegister() = default;
    IObjectRegister( const IObjectRegister& val ) = delete;
    virtual ~IObjectRegister() = default;

    IObjectRegister& operator=( const IObjectRegister& rhv ) = delete;

    virtual void addObject( IObject* object ) = 0;
    virtual void removeObject( IObject* object ) = 0;

protected:
private:
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )