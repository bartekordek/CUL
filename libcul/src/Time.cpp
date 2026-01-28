#include "CUL/Time.hpp"
#include "IMPORT_datetime.hpp"
#include "CUL/Proifling/Profiler.hpp"
#include "CUL/ITimer.hpp"
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
    m_initialized = true;
}

Time::Time( const Time& rhv ) : m_ns( rhv.m_ns ), m_dateTime( std::make_unique<jed_utils::datetime>() ), m_asString( rhv.m_asString )
{
    *m_dateTime = *rhv.m_dateTime;
    m_initialized = true;
}

Time::Time( Time&& rhv ):
    m_ns( rhv.m_ns ),
    m_dateTime( std::move( m_dateTime ) ),
    m_asString( std::move( rhv.m_asString ) )
{
    m_initialized = true;
}

Time& Time::operator=( const Time& rhv )
{
    if( &rhv != this )
    {
        *m_dateTime = *rhv.m_dateTime;
        m_asString = rhv.m_asString;
        m_ns = rhv.m_ns;
        m_initialized = true;
    }
    return *this;
}

Time& Time::operator=( Time&& rhv )
{
    if( &rhv != this )
    {
        waitForDateTime();
        m_dateTime = std::move( rhv.m_dateTime );
        m_ns = rhv.m_ns;
        m_asString = std::move( rhv.m_asString );
        m_initialized = true;
    }
    return *this;
}

void Time::setYear( TimeType inYear )
{
    waitForDateTime();
    *m_dateTime = jed_utils::datetime(
        inYear, m_dateTime->get_month(),
        m_dateTime->get_day(),
        m_dateTime->get_hour(),
        m_dateTime->get_minute(),
        m_dateTime->get_second() );
    updateString();
    m_initialized = true;
}

TimeType Time::getYear() const
{
    waitForDateTime();
    return m_dateTime->get_year();
}

void Time::setMonth( TimeType inMonth )
{
    waitForDateTime();
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), inMonth, m_dateTime->get_day(), m_dateTime->get_hour(),
                                       m_dateTime->get_minute(), m_dateTime->get_second() );
    updateString();
    m_initialized = true;
}

TimeType Time::getMonth() const
{
    waitForDateTime();
    return m_dateTime->get_month();
}

void Time::setDay( TimeType inDay )
{
    waitForDateTime();
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), m_dateTime->get_month(), inDay, m_dateTime->get_hour(),
                                       m_dateTime->get_minute(), m_dateTime->get_second() );
    updateString();
    m_initialized = true;
}

TimeType Time::getDay() const
{
    waitForDateTime();
    return m_dateTime->get_day();
}

void Time::setHour( TimeType inHour )
{
    waitForDateTime();
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), m_dateTime->get_month(), m_dateTime->get_day(), inHour,
                                       m_dateTime->get_minute(), m_dateTime->get_second() );
    updateString();
    m_initialized = true;
}

TimeType Time::getHour() const
{
    waitForDateTime();
    return m_dateTime->get_hour();
}

void Time::setMinute( TimeType inMinute )
{
    waitForDateTime();
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), m_dateTime->get_month(), m_dateTime->get_day(), m_dateTime->get_hour(),
                                       inMinute, m_dateTime->get_second() );
    updateString();
    m_initialized = true;
}

TimeType Time::getMinute() const
{
    waitForDateTime();
    return m_dateTime->get_minute();
}

void Time::setSecond( TimeType inSecond )
{
    waitForDateTime();
    *m_dateTime = jed_utils::datetime( m_dateTime->get_year(), m_dateTime->get_month(), m_dateTime->get_day(), m_dateTime->get_hour(),
                                       m_dateTime->get_minute(), inSecond );
    updateString();
    m_initialized = true;
}

TimeType Time::getSecond() const
{
    waitForDateTime();
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
    return m_asString.equals( arg.cStr() );
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

const CUL::StringWr& Time::toString() const
{
    if( m_asString.empty() )
    {
        updateString();
    }

    return m_asString;
}

const char* Time::cStr() const
{
    return m_asString.getUtfChar();
}

void removePrecedingZero( StringWr& inOutVal )
{
    while( ( inOutVal.empty() == false ) && ( inOutVal.startsWith( "0" ) ) && ( inOutVal.size() > 1 ) )
    {
        inOutVal.erase( 0, 1 );
    }
}

void Time::fromString( const StringWr& inString )
{
    ProfilerScope( "Time::fromString" );
    if( inString.empty() )
    {
        return;
    }
    m_asString = inString;
    m_initialized = false;
    m_initializedFuture = std::async( std::launch::async,
                                      [this]()
                                      {
                                          ProfilerScope( "Time::fromString::datetime_load" );

                                          std::vector<StringWr> dateTimeSeparated = m_asString.split( " " );

                                          std::vector<StringWr> dateSeparted = dateTimeSeparated[0].split( "-" );

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

                                          std::vector<StringWr> timeSeparated = dateTimeSeparated[01].split( ":" );
                                          for( auto& currString : timeSeparated )
                                          {
                                              removePrecedingZero( currString );
                                          }
                                          const auto hour = timeSeparated[0].toInt64();
                                          const auto minute = timeSeparated[1].toInt64();
                                          const auto seconds = timeSeparated[2].toInt64();

                                          *m_dateTime = jed_utils::datetime( year, month, day, hour, minute, seconds );
                                          m_initialized = true;
                                      } );

}

void Time::setTimeNs( std::int64_t ns )
{
    m_ns = ns;
    updateString();
}

void Time::setTimeSec( std::time_t timeConverted )
{
    ProfilerScope( "Time::setTimeSec" );
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
    m_initialized = true;
    updateString();
}

void Time::fromEpoch( std::uint64_t inSinceEpoch )
{
    ProfilerScope( "Time::fromEpoch" );
    m_asEpoch = inSinceEpoch;

    //const auto tm = localtime_xp( m_asEpoch );

    //const auto year = static_cast<TimeType>( 1900 + tm.tm_year );
    //const auto month = static_cast<TimeType>( ( tm.tm_mon + 1 ) );
    //const auto day = static_cast<TimeType>( tm.tm_mday );
    //const auto hour = static_cast<TimeType>( tm.tm_hour );
    //const auto minute = static_cast<TimeType>( tm.tm_min );
    //const auto seconds = static_cast<TimeType>( tm.tm_sec );

    //*m_dateTime = jed_utils::datetime( year, month, day, hour, minute, seconds );
    //m_ns = timeConverted * 1000000000;
    //m_initialized = true;
    //updateString();
}

void Time::updateString() const
{
    ProfilerScope( "Time::updateString" );
    waitForDateTime();
    m_asString = m_dateTime->to_string( "yyyy/MM/dd HH:mm:ss" );
}

BasicTime Time::operator-( const Time& arg ) const
{
    BasicTime result;
    waitForDateTime();
    const jed_utils::timespan diff = *this->m_dateTime - *arg.m_dateTime;

    result.Day = diff.get_days();
    result.Hour = diff.get_hours();
    result.Minute = diff.get_minutes();
    result.Seconds = diff.get_seconds();

    return result;
}

bool Time::almostTheSame( const Time& arg, std::int32_t differenceInSeconds ) const
{
    if( m_dateTime->get_year() != arg.m_dateTime->get_year() )
    {
        return false;
    }

    if( m_dateTime->get_month() != arg.m_dateTime->get_month() )
    {
        return false;
    }

    if( m_dateTime->get_day() != arg.m_dateTime->get_day() )
    {
        return false;
    }

    if( m_dateTime->get_hour() != arg.m_dateTime->get_hour() )
    {
        return false;
    }

    if( m_dateTime->get_minute() != arg.m_dateTime->get_minute() )
    {
        return false;
    }

    return std::abs( m_dateTime->get_second() - arg.m_dateTime->get_second() ) < differenceInSeconds;
}

std::uint64_t Time::dateTimeToEpoch( const BasicTime& /*inBt*/ )
{
    return std::uint64_t(0);
}

Time::~Time()
{
    waitForDateTime();
}

void Time::waitForDateTime() const
{
    while( !m_initialized )
    {
        ITimer::sleepMicroSeconds( 1 );
    }
}