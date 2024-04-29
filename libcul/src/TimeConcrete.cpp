#include "CUL/TimeConcrete.hpp"

using namespace CUL;

TimeConcrete::TimeConcrete()
{
}

TimeConcrete::TimeConcrete( const TimeConcrete& tc ):
    ITime(),
    m_ns( tc.m_ns )
{
}

TimeConcrete& TimeConcrete::operator=( const TimeConcrete& rhv )
{
    if( &rhv != this )
    {
        m_ns = rhv.m_ns;
    }
    return *this;
}

void TimeConcrete::setTimeMs( const unsigned int time )
{
    m_ns = time / 1000000.f;
}

void TimeConcrete::setTimeUs( const unsigned int us )
{
    m_ns = us * 1000.f;
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
    return result;
}

ITime& TimeConcrete::operator=( const ITime& arg )
{
    if( this != &arg )
    {
        m_ns = arg.getUs();
    }
    return *this;
}

const CUL::String& TimeConcrete::toString()
{
    m_asString = m_ns;
    return m_asString;
}

void TimeConcrete::setTimeNs( const unsigned int ns )
{
    m_ns = ns;
}

TimeConcrete::~TimeConcrete()
{
}


