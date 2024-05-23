#include "CUL/TimeConcrete.hpp"

using namespace CUL;

TimeConcrete::TimeConcrete()
{
}

TimeConcrete::TimeConcrete( const TimeConcrete& rhv )
    : ITime(),
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

TimeConcrete::TimeConcrete( TimeConcrete&& rhv )
    : ITime(),
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

TimeConcrete& TimeConcrete::operator=( const TimeConcrete& rhv )
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

TimeConcrete& TimeConcrete::operator=( TimeConcrete&& rhv )
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

void TimeConcrete::setTimeMs( const unsigned int time )
{
    m_ns = static_cast<float>( time ) / 1000000.f;
    updateString();
}

void TimeConcrete::setTimeUs( const unsigned int us )
{
    m_ns = static_cast<float>( us ) * 1000.f;
    updateString();
}

float TimeConcrete::getMs() const
{
    return m_ns / 1000000.f;
}

float TimeConcrete::getS() const
{
    return m_ns / ( 1000.f * 1000.f * 1000.f );
}

float TimeConcrete::getM() const
{
    return m_ns / ( 60000.f * 1000.f * 1000.f);
}

float TimeConcrete::getH() const
{
    return m_ns / ( 3600000.f * 1000.f  * 1000.f);
}

float TimeConcrete::getUs() const
{
    return m_ns / 1000.f;
}

bool TimeConcrete::operator==( const ITime& arg ) const
{
    return m_ns == arg.getUs();
}

bool TimeConcrete::operator<( const ITime& arg ) const
{
    return m_ns < arg.getUs();
}

bool TimeConcrete::operator>( const ITime& arg ) const
{
    return m_ns > arg.getUs();
}

ITime* TimeConcrete::copy() const
{
    auto result = new TimeConcrete();
    result->setTimeUs( m_ns );
    result->updateString();
    return result;
}

ITime& TimeConcrete::operator=( const ITime& arg )
{
    if( this != &arg )
    {
        m_ns = arg.getUs();
        updateString();
    }
    return *this;
}

const CUL::String& TimeConcrete::toString()
{
    return m_asString;
}

void TimeConcrete::setTimeNs( const unsigned int ns )
{
    m_ns = ns;
    updateString();
}

void TimeConcrete::updateString()
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

TimeConcrete::~TimeConcrete()
{
}