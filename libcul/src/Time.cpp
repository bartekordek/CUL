#include "CUL/Time.hpp"
#include "IMPORT_datetime.hpp"
#include "CUL/STL_IMPORTS/STD_sstream.hpp"

using namespace CUL;

inline std::tm localtime_xp( std::time_t* timer )
{
    std::tm bt{};
#if defined( __unix__ )
    localtime_r( timer, &bt );
#elif defined( _MSC_VER )
    localtime_s( &bt, timer );
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock( mtx );
    bt = *std::localtime( timer );
#endif
    return bt;
}

Time::Time() : m_dateTime( std::make_unique<jed_utils::datetime>() )
{
}

Time::Time( std::int32_t inYear, std::int32_t inMonth, std::int32_t inDay, std::int32_t inHour, std::int32_t inMinute,
            std::int32_t inSeconds )
    : m_dateTime( std::make_unique<jed_utils::datetime>() )
{
    *m_dateTime = jed_utils::datetime( inYear, inMonth, inDay, inHour, inMinute, inSeconds );
}

Time::Time( const Time& rhv ) : m_ns( rhv.m_ns ), m_dateTime( std::make_unique<jed_utils::datetime>() ), m_asString( rhv.m_asString )
{
    *m_dateTime = *rhv.m_dateTime;
}

Time::Time( Time&& rhv ):
    m_ns( rhv.m_ns ),
    m_dateTime( std::move( m_dateTime ) ),
    m_asString( std::move( rhv.m_asString ) )
{
}

Time& Time::operator=( const Time& rhv )
{
    if( &rhv != this )
    {
        *m_dateTime = *rhv.m_dateTime;
        m_asString = rhv.m_asString;
        m_ns = rhv.m_ns;
    }
    return *this;
}

Time& Time::operator=( Time&& rhv )
{
    if( &rhv != this )
    {
        m_dateTime = std::move( rhv.m_dateTime );
        m_ns = rhv.m_ns;
        m_asString = std::move( rhv.m_asString );
    }
    return *this;
}

void Time::setYear( TimeType inYear )
{
    *m_dateTime = jed_utils::datetime(
        inYear, m_dateTime->get_month(),
        m_dateTime->get_day(),
        m_dateTime->get_hour(),
        m_dateTime->get_minute(),
        m_dateTime->get_second() );
}

TimeType Time::getYear() const
{
    return m_dateTime->get_year();
}

void Time::setMonth( TimeType inMonth )
{
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), inMonth, m_dateTime->get_day(), m_dateTime->get_hour(),
                                       m_dateTime->get_minute(), m_dateTime->get_second() );
}

TimeType Time::getMonth() const
{
    return m_dateTime->get_month();
}

void Time::setDay( TimeType inDay )
{
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), m_dateTime->get_month(), inDay, m_dateTime->get_hour(),
                                       m_dateTime->get_minute(), m_dateTime->get_second() );
}

TimeType Time::getDay() const
{
    return m_dateTime->get_day();
}

void Time::setHour( TimeType inHour )
{
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), m_dateTime->get_month(), m_dateTime->get_day(), inHour,
                                       m_dateTime->get_minute(), m_dateTime->get_second() );
}

TimeType Time::getHour() const
{
    return m_dateTime->get_hour();
}

void Time::setMinute( TimeType inMinute )
{
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), m_dateTime->get_month(), m_dateTime->get_day(), m_dateTime->get_hour(),
                                       inMinute, m_dateTime->get_second() );
}

TimeType Time::getMinute() const
{
    return m_dateTime->get_minute();
}

void Time::setSecond( TimeType inSecond )
{
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), m_dateTime->get_month(), m_dateTime->get_day(), m_dateTime->get_hour(),
                                       m_dateTime->get_minute(), inSecond );
}

TimeType Time::getSecond() const
{
    return m_dateTime->get_second();
}

void Time::setTimeMs( std::int64_t time )
{
    m_ns = static_cast<float>( time ) / 1000000.f;
    updateString();
}

void Time::setTimeUs( std::int64_t us )
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

const CUL::String& Time::toString() const
{
    return m_asString;
}

const char* Time::cStr() const
{
    return m_asString.cStr();
}

void removePrecedingZero( String& inOutVal )
{
    while( ( inOutVal.empty() == false ) && ( inOutVal.doesBeginWith( "0" ) ) && ( inOutVal.size() > 1u ) )
    {
        inOutVal.erase( 0u );
    }
}

void Time::fromString( const String& inString )
{
    if( inString.empty() )
    {
        return;
    }

    std::vector<String> dateTimeSeparated = inString.split( " " );

    std::vector<String> dateSeparted = dateTimeSeparated[0].split( "-" );

    if( dateSeparted.size() < 3u )
    {
        dateSeparted = dateTimeSeparated[0].split( "/" );
    }

    for( auto& currString : dateSeparted )
    {
        removePrecedingZero( currString );
    }

    const auto year = dateSeparted[0].toInt64();
    const auto month = dateSeparted[1].toInt64();
    const auto day = dateSeparted[2].toInt64();

    std::vector<String> timeSeparated = dateTimeSeparated[01].split( ":" );
    for( auto& currString : timeSeparated )
    {
        removePrecedingZero( currString );
    }
    const auto hour = timeSeparated[0].toInt64();
    const auto minute = timeSeparated[1].toInt64();
    const auto seconds = timeSeparated[2].toInt64();

    m_asString = inString;
    *m_dateTime = jed_utils::datetime( year, month, day, hour, minute, seconds );
}

void Time::setTimeNs( std::int64_t ns )
{
    m_ns = ns;
    updateString();
}

void Time::setTimeSec( std::time_t timeConverted )
{
    m_asEpoch = static_cast<decltype( m_asEpoch )>( timeConverted );

    const auto tm = localtime_xp( &timeConverted );

    const auto year = static_cast<TimeType>( 1900 + tm.tm_year );
    const auto month = static_cast<TimeType>( ( tm.tm_mon + 1 ) );
    const auto day = static_cast<TimeType>( tm.tm_mday );
    const auto hour = static_cast<TimeType>( tm.tm_hour );
    const auto minute = static_cast<TimeType>( tm.tm_min );
    const auto seconds = static_cast<TimeType>( tm.tm_sec );

    *m_dateTime = jed_utils::datetime( year, month, day, hour, minute, seconds );
    m_ns = timeConverted * 1000000000;
    updateString();
}

void Time::updateString()
{
    m_asString = m_dateTime->to_string( "yyyy/MM/dd hh:mm:ss" );
}

BasicTime Time::operator-( const Time& arg ) const
{
    BasicTime result;
    const jed_utils::timespan diff = *this->m_dateTime - *arg.m_dateTime;

    result.Day = diff.get_days();
    result.Hour = diff.get_hours();
    result.Minute = diff.get_minutes();
    result.Seconds = diff.get_seconds();

    return result;
}

std::uint64_t Time::dateTimeToEpoch( const BasicTime& /*inBt*/ )
{
    return std::uint64_t(0);
}

Time::~Time()
{
}