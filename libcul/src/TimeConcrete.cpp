#include "CUL/TimeConcrete.hpp"

using namespace CUL;

TimeConcrete::TimeConcrete()
{
}

TimeConcrete::TimeConcrete( const TimeConcrete& tc ):
    ITime(),
    m_us( tc.m_us )
{
}

TimeConcrete& TimeConcrete::operator=( const TimeConcrete& rhv )
{
    if( &rhv != this )
    {
        m_us = rhv.m_us;
    }
    return *this;
}

void TimeConcrete::setTimeMs( const unsigned int time )
{
    m_us = time / 1000;
}

void TimeConcrete::setTimeUs( const unsigned int us )
{
    m_us = us;
}

float TimeConcrete::getMs() const
{
    return m_us / 1000;
}

float TimeConcrete::getS() const
{
    return m_us / ( 1000.f * 1000.f );
}

float TimeConcrete::getM() const
{
    return m_us / ( 60000.f * 1000.f );
}

float TimeConcrete::getH() const
{
    return m_us / ( 3600000.f * 1000.f );
}

float TimeConcrete::getUs() const
{
    return m_us;
}

bool TimeConcrete::operator==( const ITime& arg ) const
{
    return m_us == arg.getUs();
}

bool TimeConcrete::operator<( const ITime& arg ) const
{
    return m_us < arg.getUs();
}

bool TimeConcrete::operator>( const ITime& arg ) const
{
    return m_us > arg.getUs();
}

ITime* TimeConcrete::copy() const
{
    auto result = new TimeConcrete();
    result->setTimeUs( m_us );
    return result;
}

ITime& TimeConcrete::operator=( const ITime& arg )
{
    if( this != &arg )
    {
        m_us = arg.getUs();
    }
    return *this;
}

const CUL::String& TimeConcrete::toString()
{
    m_asString = m_us;
    return m_asString;
}

TimeConcrete::~TimeConcrete()
{
}