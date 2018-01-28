#include "CUL/Math/Degree.hpp"

using namespace CUL;
using namespace Math;

Degree::Degree()
{

}

Degree::~Degree()
{

}

const double Degree::getValueD()const
{
    return this->m_val;
}

const int Degree::getValueI()const
{
    return static_cast<int>( this->m_val );
}

Degree& Degree::operator=( const double val )
{
    this->m_val = val;
    return *this;
}

Degree& Degree::operator=( const int val )
{
    this->m_val = static_cast<double>( val );
    return *this;
}