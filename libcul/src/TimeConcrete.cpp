#include "TimeConcrete.hpp"

using namespace CUL;

TimeConcrete::TimeConcrete()
{
}

TimeConcrete::TimeConcrete( const TimeConcrete& tc ):
    m_us( tc.m_us )
{
}

TimeConcrete::~TimeConcrete()
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

void TimeConcrete::setTimeMs( const double time )
{
    m_us = 1.0 * time / 1000.0;
}

void TimeConcrete::setTimeUs( const double us )
{
    m_us = us;
}

const double TimeConcrete::getMs() const
{
    return m_us * 1000.0;
}

const double TimeConcrete::getS() const
{
    return m_us / ( 1000 * 1000 );
}

const double TimeConcrete::getM() const
{
    return m_us / ( 60000 * 1000 );
}

const double TimeConcrete::getH() const
{
    return m_us / ( 3600000.0 * 1000.0 );
}

const double TimeConcrete::getUs() const
{
    return m_us;
}
