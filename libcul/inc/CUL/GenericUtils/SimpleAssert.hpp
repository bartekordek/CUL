#pragma once

#include <CUL/CUL.hpp>
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API Assert
{
public:
    static void simple( bool val, const String& msg = String( "" ) );
protected:
private:
};

NAMESPACE_END( CUL )