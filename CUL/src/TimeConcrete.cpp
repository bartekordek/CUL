#include "TimeConcrete.hpp"
using namespace CUL;
TimeConcrete::TimeConcrete( void )
{
}

TimeConcrete::~TimeConcrete()
{
}

void TimeConcrete::setTimeMs( const unsigned int time )
{
    this->ms = time;
}

const unsigned int TimeConcrete::getMs()const
{
    return this->ms;
}

const unsigned int TimeConcrete::getS()const
{
    return this->ms / 1000;
}

const unsigned int TimeConcrete::getM()const
{
    return this->ms / 60000;
}

const unsigned TimeConcrete::getH()const
{
    return this->ms / 3600000;
}