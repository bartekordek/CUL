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

    std::uint16_t getYear() const;
    void setYear( std::uint16_t inYear );

    std::uint8_t getMonth() const;
    void setMonth( std::uint8_t inMonth );

    std::uint8_t getDay() const;
    void setDay( std::uint8_t inDay );

    std::uint8_t getHour() const;
    void setHour( std::uint8_t inHour );

    std::uint8_t getMinute() const;
    void setMinute( std::uint8_t inMinute );

    std::uint8_t getSecond() const;
    void setSecond( std::uint8_t inSecond );

    std::uint16_t getMiliSecond() const;
    void setMiliSecond( std::uint16_t inMiliSecond );

    bool operator==( const Time& ) const;
    bool operator<( const Time& ) const;
    bool operator>( const Time& ) const;

    Time* copy() const;
    const CUL::String& toString();

    ~Time();

protected:
private:
    void updateString();
    float m_ns{ 0.f };
    std::uint16_t m_year{ 0u };
    std::uint8_t m_month{ 0u };
    std::uint8_t m_day{ 0u };
    std::uint8_t m_hour{ 0u };
    std::uint8_t m_minute{ 0u };
    std::uint8_t m_second{ 0u };
    std::uint8_t m_miliseond{ 0u };
    std::uint8_t m_wday{ 0u };
    CUL::String m_asString;
};

NAMESPACE_END( CUL )