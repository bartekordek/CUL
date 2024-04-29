#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API ITime
{
public:
    ITime() = default;

    virtual void setTimeMs( const unsigned int time ) = 0;
    virtual void setTimeUs( const unsigned int us ) = 0;
    virtual void setTimeNs( const unsigned int us ) = 0;
    virtual float getMs() const = 0;
    virtual float getS() const = 0;
    virtual float getM() const = 0;
    virtual float getH() const = 0;
    virtual float getUs() const = 0;
    virtual bool operator==( const ITime& ) const = 0;
    virtual bool operator<( const ITime& ) const = 0;
    virtual bool operator>( const ITime& ) const = 0;

    virtual ITime& operator=( const ITime& arg ) = 0;

    virtual ITime* copy() const = 0;

    virtual ~ITime();
protected:
private:
    ITime( const ITime& arg ) = delete;
    ITime( ITime&& arg ) = delete;
    
    ITime& operator=( ITime&& arg ) = delete;
};

NAMESPACE_END( CUL )