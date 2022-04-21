#pragma once

#include <CUL/CUL.hpp>
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

NAMESPACE_BEGIN( LOG )
class ILogger;
NAMESPACE_END( LOG )

class CULLib_API Assert
{
public:
    static void simple( bool val, const String& msg = String( "" ), LOG::ILogger* loggerIn = nullptr );
protected:
private:
};

NAMESPACE_END( CUL )