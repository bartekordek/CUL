#pragma once

#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using CDbl = const double;

class CULLib_API ISize3DD
{
public:
    ISize3DD() = default;
    virtual ~ISize3DD() = default;

    virtual void setWidth( CDbl val ) = 0;
    virtual void setHeight( CDbl val ) = 0;
    virtual void setDepth( CDbl val ) = 0;

    virtual void setWidthHeightDepth( CDbl width, CDbl height, CDbl depth ) = 0;

    virtual CDbl getWidth() const = 0;
    virtual CDbl getHeight() const = 0;
    virtual CDbl getDepth() const = 0;

protected:
private:
    ISize3DD( const ISize3DD& val ) = delete;
    ISize3DD& operator=( const ISize3DD& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )