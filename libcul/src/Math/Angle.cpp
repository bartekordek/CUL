#include "CUL/Math/Angle.hpp"
#include "CUL/Math/Math.hpp"

using namespace CUL;
using namespace MATH;

Angle::Angle()
{
}

Angle::Angle( Cdouble value, const Type type )
{
    setValue( value, type );
}

Angle::Angle( Cint value, const Type type )
{
    setValue( value, type );
}

int Angle::getValueI( const Type type ) const
{
    return static_cast<int>( getValueD( type ) );
}

void Angle::setValue( Cint value, const Type type )
{
    setValue( static_cast<double>( value ), type );
}

void Angle::setIncrementValue( Cunt value )
{
    setIncrementValue( static_cast<double>( value ) );
}

void Angle::setIncrementValue( Cint value )
{
    setIncrementValue( static_cast<double>( value ) );
}

void Angle::setIncrementValue( Cdouble value )
{
    m_incrementValue = value;
}

Angle::Type Angle::getCurrentType() const
{
    return m_type;
}

void Angle::setCurrentType( const Type type )
{
    m_type = type;
}

Angle& Angle::operator+=( Cunt val )
{
    add( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator+=( Cint val )
{
    add( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator+=( Cdouble value )
{
    add( value );
    return *this;
}

Angle& Angle::operator-=( Cunt val )
{
    subtrackt( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator-=( Cint val )
{
    subtrackt( static_cast<double>( val ) );
    return *this;
}

Angle Angle::operator/( Cdouble val )
{
    Angle result( *this );
    result /= val;
    return result;
}

Angle Angle::operator/( Cint val )
{
    Angle result( *this );
    result /= val;
    return result;
}

Angle Angle::operator/( Cunt val )
{
    Angle result( *this );
    result /= val;
    return result;
}

Angle& Angle::operator/=( Cdouble value )
{
    divide( static_cast<double>( value ) );
    return *this;
}

Angle& Angle::operator/=( Cint val )
{
    divide( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator/=( Cunt val )
{
    divide( static_cast<double>( val ) );
    return *this;
}

void Angle::divide( Cdouble value )
{
    if( Type::RADIAN == m_type )
    {
        m_valueRad /= value;
        m_valueDeg = radian2degree( m_valueRad );
    }
    else
    {
        m_valueDeg /= value;
        m_valueRad = degree2radian( m_valueDeg );
    }
}

Angle& Angle::operator*=( Cdouble val )
{
    multiply( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator*=( Cint val )
{
    multiply( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator*=( Cunt val )
{
    multiply( static_cast<double>( val ) );
    return *this;
}

void Angle::add( Cdouble value )
{
    if( Type::RADIAN == m_type )
    {
        m_valueRad += value;
        m_valueDeg = radian2degree( m_valueRad );
    }
    else
    {
        m_valueDeg += value;
        m_valueRad = degree2radian( m_valueDeg );
    }
}

void Angle::subtrackt( Cdouble value )
{
    if( Type::RADIAN == m_type )
    {
        m_valueRad -= value;
        m_valueDeg = radian2degree( m_valueRad );
    }
    else
    {
        m_valueDeg -= value;
        m_valueRad = degree2radian( m_valueDeg );
    }
}

void Angle::multiply( Cdouble value )
{
    if( Type::RADIAN == m_type )
    {
        m_valueRad *= value;
        m_valueDeg = radian2degree( m_valueRad );
    }
    else
    {
        m_valueDeg *= value;
        m_valueRad = degree2radian( m_valueDeg );
    }
}

Angle Angle::operator*( Cdouble val )
{
    Angle result( *this );
    result *= val;
    return result;
}

Angle Angle::operator*( Cint val )
{
    Angle result( *this );
    result *= val;
    return result;
}

Angle Angle::operator*( Cunt val )
{
    Angle result( *this );
    result *= val;
    return result;
}

Angle& Angle::operator++()
{
    increment();
    return *this;
}

Angle& Angle::operator--()
{
    decrement();
    return *this;
}

Angle Angle::operator++( int )
{
    Angle result( *this );
    increment();
    return result;
}

Angle Angle::operator--( int )
{
    Angle result( *this );
    decrement();
    return result;
}

void Angle::increment()
{
    if( Type::RADIAN == m_type )
    {
        m_valueRad += m_incrementValue;
    }
    else
    {
        m_valueDeg += m_incrementValue;
    }
}

void Angle::decrement()
{
    if( Type::RADIAN == m_type )
    {
        m_valueRad -= m_incrementValue;
    }
    else
    {
        m_valueDeg -= m_incrementValue;
    }
}

Angle& Angle::operator-=( Cdouble value )
{
    if( Type::RADIAN == m_type )
    {
        m_valueRad -= value;
        m_valueDeg = radian2degree( m_valueRad );
    }
    else
    {
        m_valueDeg -= value;
        m_valueRad = degree2radian( m_valueDeg );
    }
    return *this;
}

void Angle::setValue( Cunt value, const Type type )
{
    setValue( static_cast<double>( value ), type );
}

void Angle::setValue( Cdouble value, const Type type )
{
    if( Type::RADIAN == type )
    {
        m_valueRad = value;
        m_valueDeg = radian2degree( value );
    }
    else
    {
        m_valueDeg = value;
        m_valueRad = degree2radian( value );
    }
    m_type = type;
}

double Angle::getValueD( const Type type ) const
{
    if( Type::RADIAN == type )
    {
        return m_valueRad;
    }
    return m_valueDeg;
}

float Angle::getValueF( const Type type ) const
{
    if( Type::RADIAN == type )
    {
        return static_cast<float>( m_valueRad );
    }
    return static_cast<float>( m_valueDeg );
}

// ASUMPTION!
// We are returning radian.
// Why? Mostly, if people want Degrees, they want them to be integer.
Angle::operator double() const
{
    return m_valueRad;
}

Angle::operator int() const
{
    return static_cast<int>( m_valueDeg );
}


Angle::~Angle()
{
}


double CUL::MATH::radian2degree( Cdouble radian )
{
    return radian * 180.0 / CUL::MATH::UTIL::Constants::PI;
}

double CUL::MATH::degree2radian( Cdouble degree )
{
    return degree * CUL::MATH::UTIL::Constants::PI / 180.0;
}

float CUL::MATH::radian2degree( const float radian )
{
    return radian * 180.0f / static_cast<float>( CUL::MATH::UTIL::Constants::PI );
}

float CUL::MATH::degree2radian( const float degree )
{
    return degree * static_cast<float>( CUL::MATH::UTIL::Constants::PI ) / 180.0f;
}