#pragma once

#include "CUL/ITime.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
class CULLib_API TimeConcrete final: public ITime
{
public:
    TimeConcrete();
    TimeConcrete( const TimeConcrete& tc );

    TimeConcrete& operator=( const TimeConcrete& rhv );
    void setTimeMs( const unsigned int ms ) override;
    void setTimeUs( const unsigned int us ) override;
    unsigned int getMs() const override;
    unsigned int getS() const override;
    unsigned int getM() const override;
    unsigned int getH() const override;
    unsigned int getUs() const override;

    bool operator==( const ITime& arg ) const override;
    bool operator<( const ITime& arg ) const override;
    bool operator>( const ITime& arg ) const override;
    ITime* copy() const override;
    ITime& operator=( const ITime& arg ) override;

    const CUL::String& toString();

    ~TimeConcrete();
protected:
private:
    unsigned int m_us = 0;
    CUL::String m_asString;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )