#include "CUL/Math/Degree.hpp"
#include "CUL/Math/Math.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

Degree::Degree()
{

}

Degree::Degree( const double angle ):
    m_val( angle )
{

}

Degree::Degree( const int angle ):
    m_val( static_cast<double>( angle ) )
{

}

Degree::Degree( const IAngle& degree )
{
    if( IAngle::Type::DEGREE == degree.getType() )
    {
        this->m_val = degree.getValueD();
    }
    else if( IAngle::Type::RADIAN == degree.getType() )
    {
        this->m_val = degree.getValueD() * Util::Constants::PI / 180.0;
    }
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

const IAngle::Type Degree::getType()const
{
    return IAngle::Type::DEGREE;
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

IAngle& Degree::operator+=( const double val )
{
    this->m_val += val;
    return *this;
}

IAngle& Degree::operator+=( const int val )
{
    this->m_val += static_cast<double>( val );
    return *this;
}

IAngle& Degree::operator-=( const double val )
{
    this->m_val -= val;
    return *this;
}

IAngle& Degree::operator-=( const int val )
{
    this->m_val -= static_cast<double>( val );
    return *this;
}

NAMESPACE_END( Math )
NAMESPACE_END( CUL )
