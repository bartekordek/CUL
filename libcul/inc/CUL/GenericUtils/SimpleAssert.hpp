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
    static void simple( bool val, const char* msg = nullptr, LOG::ILogger* loggerIn = nullptr );
    static void simple( bool val, const String& msg, LOG::ILogger* loggerIn = nullptr );
    static void check( bool value, const char* msg... );

protected:
private:
    static void dumpStackTrace();
};

NAMESPACE_END( CUL )