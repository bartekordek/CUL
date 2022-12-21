#pragma once

#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( LOG )

#undef ERROR

enum class Severity: short
{
    WARN,
    INFO,
    ERROR,
    CRITICAL
};

class CULLib_API ILogger
{
public:
    ILogger() = default;
    virtual ~ILogger();

    virtual void log(
        const String& text,
        const Severity severity = Severity::INFO ) = 0;

    static ILogger* createSimpleStandardOutputLogger();
    static ILogger* getInstance();

protected:

private:
    static ILogger* s_instance;
private:
    ILogger( const ILogger& arg ) = delete;
    ILogger& operator=( const ILogger& arg ) = delete;
};

NAMESPACE_END( LOG )
NAMESPACE_END( CUL )