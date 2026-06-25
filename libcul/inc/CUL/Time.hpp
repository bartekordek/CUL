#pragma once

#include "CUL/String/StringWrapper.hpp"

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

class Time final
{
public:
    CULLib_API Time();
    CULLib_API Time( std::int32_t inYear,
                     std::int32_t inMonth,
                     std::int32_t inDay,
                     std::int32_t inHour,
                     std::int32_t inMinute,
                     std::int32_t inSeconds );

    CULLib_API Time( const Time& arg );
    CULLib_API Time( Time&& arg );
    CULLib_API Time& operator=( const Time& arg );
    CULLib_API Time& operator=( Time&& arg );

    CULLib_API void setTimeMs( std::int64_t time );
    CULLib_API void setTimeUs( std::int64_t us );
    CULLib_API void setTimeNs( std::int64_t us );
    CULLib_API void setTimeSec( std::time_t sec );
    CULLib_API float getMs() const;
    CULLib_API float getS() const;
    CULLib_API float getM() const;
    CULLib_API float getH() const;
    CULLib_API float getUs() const;

    CULLib_API void setDate( TimeType inYear, TimeType inMonth, TimeType inDay );

    CULLib_API TimeType getYear() const;
    CULLib_API void setYear( TimeType inYear );

    CULLib_API TimeType getMonth() const;
    CULLib_API void setMonth( TimeType inMonth );

    CULLib_API TimeType getDay() const;
    CULLib_API void setDay( TimeType inDay );

    CULLib_API TimeType getHour() const;
    CULLib_API void setHour( TimeType inHour );

    CULLib_API TimeType getMinute() const;
    CULLib_API void setMinute( TimeType inMinute );

    CULLib_API TimeType getSecond() const;
    CULLib_API void setSecond( TimeType inSecond );

    CULLib_API void fromEpoch( std::uint64_t inSinceEpoch );

    CULLib_API bool operator==( const Time& ) const;
    CULLib_API bool operator<( const Time& ) const;
    CULLib_API bool operator>( const Time& ) const;

    CULLib_API Time* copy() const;
    CULLib_API const StringWr& toString() const;
    CULLib_API const char* cStr() const;
    CULLib_API void fromString( const StringWr& inString );

    static std::uint64_t dateTimeToEpoch( const BasicTime& inBt );

    CULLib_API BasicTime operator-( const Time& arg ) const;

    CULLib_API bool almostTheSame( const Time& arg,
                                   std::int32_t differenceInSeconds ) const;

    CULLib_API ~Time();

protected:
private:
    void updateString() const;
    void waitForDateTime() const;

    float m_ns{ 0.f };
    std::unique_ptr<jed_utils::datetime> m_dateTime;
    mutable StringWr m_asString;
    std::uint64_t m_asEpoch;

    bool m_initialized{ true };
    std::future<void> m_initializedFuture;
};

NAMESPACE_END( CUL )