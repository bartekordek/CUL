#include "CUL/Time.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"

using namespace CUL;

Time::Time()
{
}

Time::Time( const Time& rhv )
    : m_ns( rhv.m_ns ),
      m_year( rhv.m_year ),
      m_month( rhv.m_month ),
      m_day( rhv.m_day ),
      m_hour( rhv.m_hour ),
      m_minute( rhv.m_minute ),
      m_second( rhv.m_second ),
      m_miliseond( rhv.m_miliseond ),
      m_wday( rhv.m_wday ),
      m_asString( rhv.m_asString )
{
}

Time::Time( Time&& rhv )
    : m_ns( rhv.m_ns ),
      m_year( rhv.m_year ),
      m_month( rhv.m_month ),
      m_day( rhv.m_day ),
      m_hour( rhv.m_hour ),
      m_minute( rhv.m_minute ),
      m_second( rhv.m_second ),
      m_miliseond( rhv.m_miliseond ),
      m_wday( rhv.m_wday ),
      m_asString( std::move( rhv.m_asString ) )
{
}

Time& Time::operator=( const Time& rhv )
{
    if( &rhv != this )
    {
        m_ns = rhv.m_ns;
        m_year = rhv.m_year;
        m_month = rhv.m_month;
        m_day = rhv.m_day;
        m_hour = rhv.m_hour;
        m_minute = rhv.m_minute;
        m_second = rhv.m_second;
        m_miliseond = rhv.m_miliseond;
        m_wday = rhv.m_wday;
        m_asString = rhv.m_asString;
    }
    return *this;
}

Time& Time::operator=( Time&& rhv )
{
    if( &rhv != this )
    {
        m_ns = rhv.m_ns;
        m_year = rhv.m_year;
        m_month = rhv.m_month;
        m_day = rhv.m_day;
        m_hour = rhv.m_hour;
        m_minute = rhv.m_minute;
        m_second = rhv.m_second;
        m_miliseond = rhv.m_miliseond;
        m_wday = rhv.m_wday;
        m_asString = std::move( rhv.m_asString );
    }
    return *this;
}

void Time::setYear( std::uint16_t inYear )
{
    m_year = inYear;
}

std::uint16_t Time::getYear() const
{
    return m_year;
}

void Time::setMonth( std::uint8_t inMonth )
{
    m_month = inMonth;
}

std::uint8_t Time::getMonth() const
{
    return m_month;
}

void Time::setDay( std::uint8_t inDay )
{
    m_day = inDay;
}

std::uint8_t Time::getDay() const
{
    return m_day;
}

void Time::setHour( std::uint8_t inHour )
{
    m_hour = inHour;
}

std::uint8_t Time::getHour() const
{
    return m_hour;
}

void Time::setMinute( std::uint8_t inMinute )
{
    m_minute = inMinute;
}

std::uint8_t Time::getMinute() const
{
    return m_minute;
}

void Time::setSecond( std::uint8_t inSecond )
{
    m_second = inSecond;
}

std::uint8_t Time::getSecond() const
{
    return m_second;
}

void Time::setMiliSecond( std::uint16_t inMiliSecond )
{
    m_miliseond = inMiliSecond;
}

std::uint16_t Time::getMiliSecond() const
{
    return m_miliseond;
}

void Time::setTimeMs( std::uint64_t time )
{
    m_ns = static_cast<float>( time ) / 1000000.f;
    updateString();
}

void Time::setTimeUs( std::uint64_t us )
{
    m_ns = static_cast<float>( us ) * 1000.f;
    updateString();
}

float Time::getMs() const
{
    return m_ns / 1000000.f;
}

float Time::getS() const
{
    return m_ns / ( 1000.f * 1000.f * 1000.f );
}

float Time::getM() const
{
    return m_ns / ( 60000.f * 1000.f * 1000.f );
}

float Time::getH() const
{
    return m_ns / ( 3600000.f * 1000.f * 1000.f );
}

float Time::getUs() const
{
    return m_ns / 1000.f;
}

bool Time::operator==( const Time& arg ) const
{
    return m_ns == arg.getUs();
}

bool Time::operator<( const Time& arg ) const
{
    return m_ns < arg.getUs();
}

bool Time::operator>( const Time& arg ) const
{
    return m_ns > arg.getUs();
}

Time* Time::copy() const
{
    auto result = new Time();
    result->setTimeUs( m_ns );
    result->updateString();
    return result;
}

const CUL::String& Time::toString()
{
    return m_asString;
}

void Time::setTimeNs( std::uint64_t ns )
{
    m_ns = ns;
    updateString();
}

void Time::setTimeSec( std::uint64_t timeConverted )
{
    constexpr std::int32_t SECS_DAY = 60 * 60 * 24;
    const std::int32_t dayclock = (std::int32_t)timeConverted % SECS_DAY;
    const std::int32_t dayno = (std::int32_t)timeConverted / SECS_DAY;

    m_second = static_cast<std::uint16_t>( dayclock % 60 );
    m_minute = static_cast<std::uint16_t>( ( dayclock % 3600 ) / 60 );
    m_hour = static_cast<std::uint16_t>( dayclock / 3600 );
    m_wday = static_cast<std::uint16_t>( ( dayno + 4 ) % 7 ); /* day 0 was a thursday */

    const std::time_t timeT = static_cast<std::time_t>( timeConverted );
    const auto tm = std::localtime( &timeT );

    m_year = static_cast<std::uint16_t>( 1900 + tm->tm_year );
    m_month = static_cast<std::uint16_t>( ( tm->tm_mon + 1 ) );
    m_day = static_cast<std::uint16_t>( tm->tm_mday );
    m_hour = static_cast<std::uint16_t>( tm->tm_hour );
    m_minute = static_cast<std::uint16_t>( tm->tm_min );
    m_second = static_cast<std::uint16_t>( tm->tm_sec );

    std::tm ts = *std::localtime( &timeT );
    char buf[80];
    strftime( buf, sizeof( buf ), "%Y-%m-%d %H:%M:%S", &ts );
    m_asString = buf;
    m_ns = timeConverted * 1000000000;
}

void Time::updateString()
{
    m_asString = std::to_string( m_year );
    m_asString += "/";
    if( m_month < 10u )
    {
        m_asString += "0";
    }
    m_asString += std::to_string( m_month );
    m_asString += "/";

    if( m_day < 10u )
    {
        m_asString += "0";
    }

    m_asString += std::to_string( m_day );
    m_asString += " ";
    if( m_hour < 10u )
    {
        m_asString += "0";
    }
    m_asString += std::to_string( m_hour );
    m_asString += ":";
    if( m_minute < 10u )
    {
        m_asString += "0";
    }
    m_asString += std::to_string( m_minute );
    m_asString += ":";
    m_asString += std::to_string( m_second );
}

Time::~Time()
{
}