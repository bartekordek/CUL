#pragma once

#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( LOG )

#undef ERROR

enum class Severity: short
{
    Warn,
    Info,
    Error,
    Critical
};

class CULLib_API ILogger
{
public:
    ILogger();
    virtual ~ILogger();

    virtual void log( const String& text, const Severity severity = Severity::Info ) = 0;
    virtual void log( const char* text, const Severity severity = Severity::Info ) = 0;
    virtual void log( const wchar_t* text, const Severity severity = Severity::Info ) = 0;
    virtual void logVariable( Severity severity, const char* msg... ) = 0;
    static ILogger& getInstance();

protected:
private:
    static ILogger* s_instancePtr;

private:
    ILogger( const ILogger& arg ) = delete;
    ILogger& operator=( const ILogger& arg ) = delete;
};

NAMESPACE_END( LOG )
NAMESPACE_END( CUL )