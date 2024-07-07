#include "CUL/Time.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"

using namespace CUL;


Time::Time()
{
}

Time::Time( const Time& rhv ):
      m_ns( rhv.m_ns ),
      m_years( rhv.m_years ),
      m_months( rhv.m_months ),
      m_days( rhv.m_days ),
      m_hours( rhv.m_hours ),
      m_minutes( rhv.m_minutes ),
      m_seconds( rhv.m_seconds ),
      m_miliseonds( rhv.m_miliseonds ),
      m_wday( rhv.m_wday ),
      m_asString( rhv.m_asString )
{
}

Time::Time( Time&& rhv ):
      m_ns( rhv.m_ns ),
      m_years( rhv.m_years ),
      m_months( rhv.m_months ),
      m_days( rhv.m_days ),
      m_hours( rhv.m_hours ),
      m_minutes( rhv.m_minutes ),
      m_seconds( rhv.m_seconds ),
      m_miliseonds( rhv.m_miliseonds ),
      m_wday( rhv.m_wday ),
      m_asString( std::move( rhv.m_asString ) )
{
}

Time& Time::operator=( const Time& rhv )
{
    if( &rhv != this )
    {
        m_ns = rhv.m_ns;
        m_years = rhv.m_years;
        m_months = rhv.m_months;
        m_days = rhv.m_days;
        m_hours = rhv.m_hours;
        m_minutes = rhv.m_minutes;
        m_seconds = rhv.m_seconds;
        m_miliseonds = rhv.m_miliseonds;
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
        m_years = rhv.m_years;
        m_months = rhv.m_months;
        m_days = rhv.m_days;
        m_hours = rhv.m_hours;
        m_minutes = rhv.m_minutes;
        m_seconds = rhv.m_seconds;
        m_miliseonds = rhv.m_miliseonds;
        m_wday = rhv.m_wday;
        m_asString = std::move( rhv.m_asString );
    }
    return *this;
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

    m_seconds = static_cast<std::uint16_t>( dayclock % 60 );
    m_minutes = static_cast<std::uint16_t>( ( dayclock % 3600 ) / 60 );
    m_hours = static_cast<std::uint16_t>( dayclock / 3600 );
    m_wday = static_cast<std::uint16_t>( ( dayno + 4 ) % 7 ); /* day 0 was a thursday */

    const std::time_t timeT = static_cast<std::time_t>( timeConverted );
    const auto tm = std::localtime( &timeT );

    m_years = static_cast<std::uint16_t>( 1900 + tm->tm_year );
    m_months = static_cast<std::uint16_t>( ( tm->tm_mon + 1 ) );
    m_days = static_cast<std::uint16_t>( tm->tm_mday );
    m_hours = static_cast<std::uint16_t>( tm->tm_hour );
    m_minutes = static_cast<std::uint16_t>( tm->tm_min );
    m_seconds = static_cast<std::uint16_t>( tm->tm_sec );

    std::tm ts = *std::localtime( &timeT );
    char buf[80];
    strftime( buf, sizeof( buf ), "%Y-%m-%d %H:%M:%S", &ts );
    m_asString = buf;
    m_ns = timeConverted * 1000000000;
}

void Time::updateString()
{
    m_asString = std::to_string( m_years );
    m_asString += "/";
    if( m_months < 10u )
    {
        m_asString += "0";
    }
    m_asString += std::to_string( m_months );
    m_asString += "/";

    if( m_days < 10u )
    {
        m_asString += "0";
    }

    m_asString += std::to_string( m_days );
    m_asString += " ";
    if( m_hours < 10u )
    {
        m_asString += "0";
    }
    m_asString += std::to_string( m_hours );
    m_asString += ":";
    if( m_minutes < 10u )
    {
        m_asString += "0";
    }
    m_asString += std::to_string( m_minutes );
    m_asString += ":";
    m_asString += std::to_string( m_seconds );
}

Time::~Time()
{
}