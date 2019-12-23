#pragma once

#include "CUL/CUL.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using CDbl = const double;

class CULLib_API IPosition3DD
{
public:
    IPosition3DD() = default;
    virtual ~IPosition3DD();

    virtual void setX( CDbl val ) = 0;
    virtual void setY( CDbl val ) = 0;
    virtual void setZ( CDbl val ) = 0;

    virtual void setXYZ( CDbl x, CDbl y, CDbl z ) = 0;

    virtual CDbl getX() const = 0;
    virtual CDbl getY() const = 0;
    virtual CDbl getZ() const = 0;

protected:
private:
    IPosition3DD( const IPosition3DD& val ) = delete;
    IPosition3DD& operator=( const IPosition3DD& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )