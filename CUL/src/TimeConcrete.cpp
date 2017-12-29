#include "TimeConcrete.hpp"

using namespace CUL;

TimeConcrete::TimeConcrete( void )
{
}

TimeConcrete::~TimeConcrete()
{
}

void TimeConcrete::setTimeMs( const double time )
{
    this->m_us = 1.0 * time / 1000.0;
}

void TimeConcrete::setTimeUs( const double us )
{
    this->m_us = us;
}

const double TimeConcrete::getMs()const
{
    return this->m_us * 1000.;
}

const double TimeConcrete::getS()const
{
    return this->m_us / (1000 * 1000);
}

const double TimeConcrete::getM()const
{
    return this->m_us / (60000 * 1000);
}

const double TimeConcrete::getH()const
{
    return this->m_us / ( 3600000.0 * 1000.0 );
}

const double TimeConcrete::getUs()const
{
    return this->m_us;
}
