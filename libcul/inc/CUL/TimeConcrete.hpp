#pragma once

#include "CUL/ITime.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 4820 )
#endif
class CULLib_API TimeConcrete final: public ITime
{
public:
    TimeConcrete();
    TimeConcrete( const TimeConcrete& tc );
    TimeConcrete( TimeConcrete&& tc );

    TimeConcrete& operator=( const TimeConcrete& rhv );
    TimeConcrete& operator=( TimeConcrete&& rhv );
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

    float m_ns = 0;
    std::uint16_t m_years = 0u;
    std::uint16_t m_months = 0u;
    std::uint16_t m_days = 0u;
    std::uint16_t m_hours = 0u;
    std::uint16_t m_minutes = 0u;
    std::uint16_t m_seconds = 0u;
    std::uint16_t m_miliseonds = 0u;
    std::uint16_t m_wday = 0u;
    CUL::String m_asString;
    void updateString();

    ~TimeConcrete();
protected:
private:
    
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )