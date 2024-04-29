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
    void setTimeNs( const unsigned int ns ) override;
    float getMs() const override;
    float getS() const override;
    float getM() const override;
    float getH() const override;
    float getUs() const override;

    bool operator==( const ITime& arg ) const override;
    bool operator<( const ITime& arg ) const override;
    bool operator>( const ITime& arg ) const override;
    ITime* copy() const override;
    ITime& operator=( const ITime& arg ) override;

    const CUL::String& toString();

    ~TimeConcrete();
protected:
private:
    float m_ns = 0;
    CUL::String m_asString;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )