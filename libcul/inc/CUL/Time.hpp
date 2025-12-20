#pragma once

#include "CUL/String.hpp"

#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"
#include "CUL/STL_IMPORTS/STD_chrono.hpp"
#include <CUL/STL_IMPORTS/STD_memory.hpp>
#include <CUL/STL_IMPORTS/STD_future.hpp>


namespace jed_utils
{
class datetime;
}


NAMESPACE_BEGIN( CUL )

using TimeType = std::int32_t;

enum class CULLib_API ETimePortion : std::uint8_t
{
    Year = 0u,
    Month,
    Day,
    Hour,
    Second,
    Milisecond
};

struct CULLib_API BasicTime
{
    TimeType Year{ 0 };
    TimeType Month{ 0 };
    TimeType Day{ 0 };
    TimeType Hour{ 0 };
    TimeType Minute{ 0 };
    TimeType Seconds{ 0 };
};

class CULLib_API Time final
{
public:
    Time();
    Time( std::int32_t inYear, std::int32_t inMonth, std::int32_t inDay, std::int32_t inHour, std::int32_t inMinute, std::int32_t inSeconds );

    Time( const Time& arg );
    Time( Time&& arg );
    Time& operator=( const Time& arg );
    Time& operator=( Time&& arg );

    void setTimeMs( std::int64_t time );
    void setTimeUs( std::int64_t us );
    void setTimeNs( std::int64_t us );
    void setTimeSec( std::time_t sec );
    float getMs() const;
    float getS() const;
    float getM() const;
    float getH() const;
    float getUs() const;

    TimeType getYear() const;
    void setYear( TimeType inYear );

    TimeType getMonth() const;
    void setMonth( TimeType inMonth );

    TimeType getDay() const;
    void setDay( TimeType inDay );

    TimeType getHour() const;
    void setHour( TimeType inHour );

    TimeType getMinute() const;
    void setMinute( TimeType inMinute );

    TimeType getSecond() const;
    void setSecond( TimeType inSecond );

    void fromEpoch( std::uint64_t inSinceEpoch );

    bool operator==( const Time& ) const;
    bool operator<( const Time& ) const;
    bool operator>( const Time& ) const;

    Time* copy() const;
    const String& toString() const;
    const char* cStr() const;
    void fromString( const String& inString );

    static std::uint64_t dateTimeToEpoch( const BasicTime& inBt );

    BasicTime operator-( const Time& arg ) const;

    bool almostTheSame( const Time& arg, std::int32_t differenceInSeconds) const;

    ~Time();

protected:
private:
    void updateString() const;
    void waitForDateTime() const;


    float m_ns{ 0.f };
    std::unique_ptr<jed_utils::datetime> m_dateTime;
    mutable CUL::String m_asString;
    std::uint64_t m_asEpoch;

    bool m_initialized{ true };
    std::future<void> m_initializedFuture;
};

NAMESPACE_END( CUL )