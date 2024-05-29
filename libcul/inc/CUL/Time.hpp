#pragma once

#include "CUL/String.hpp"

#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"
#include "CUL/STL_IMPORTS/STD_chrono.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API Time final
{
public:
    Time();

    Time( const Time& arg );
    Time( Time&& arg );
    Time& operator=( const Time& arg );
    Time& operator=( Time&& arg );

    void setTimeMs( std::uint64_t time );
    void setTimeUs( std::uint64_t us );
    void setTimeNs( std::uint64_t us );
    void setTimeSec( std::uint64_t sec );
    float getMs() const;
    float getS() const;
    float getM() const;
    float getH() const;
    float getUs() const;
    bool operator==( const Time& ) const;
    bool operator<( const Time& ) const;
    bool operator>( const Time& ) const;

    Time* copy() const;
    const CUL::String& toString();

    ~Time();

protected:
private:
    void updateString();
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
};

NAMESPACE_END( CUL )