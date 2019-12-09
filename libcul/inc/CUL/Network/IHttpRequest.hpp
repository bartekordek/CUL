#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Network )

class CULLib_API IHttpRequest
{
public:
    IHttpRequest();
    virtual ~IHttpRequest();

    virtual void setConnectionAddres( CsStr& adddress ) = 0;

    virtual void connect() = 0;

    virtual void get( CsStr& command ) = 0;

    virtual CsStr getError() = 0;

protected:
private:
};

NAMESPACE_END( Network )
NAMESPACE_END( CUL )