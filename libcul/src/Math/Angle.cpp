#include "CUL/Math/Angle.hpp"
#include "CUL/Math/Math.hpp"

using namespace CUL;
using namespace MATH;

Angle::Angle()
{
}

Angle::Angle( double value, const Type type )
{
    setValue( value, type );
}

Angle::Angle( int value, const Type type )
{
    setValue( value, type );
}

int Angle::getValueI( const Type type ) const
{
    return static_cast<int>( getValueD( type ) );
}

void Angle::setValue( int value, const Type type )
{
    setValue( static_cast<double>( value ), type );
}

void Angle::setIncrementValue( unsigned value )
{
    setIncrementValue( static_cast<double>( value ) );
}

void Angle::setIncrementValue( int value )
{
    setIncrementValue( static_cast<double>( value ) );
}

void Angle::setIncrementValue( double value )
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

Angle& Angle::operator=( float value )
{
    setValue( value, Type::RADIAN );
    return *this;
}

Angle& Angle::operator+=( const Angle& right )
{
    m_valueRad += right.m_valueRad;
    m_valueDeg += right.m_valueDeg;
    return *this;
}

Angle& Angle::operator-=( const Angle& right )
{
    m_valueRad -= right.m_valueRad;
    m_valueDeg -= right.m_valueDeg;
    return *this;
}

Angle& Angle::operator+=( unsigned val )
{
    add( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator+=( int val )
{
    add( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator+=( double value )
{
    add( value );
    return *this;
}

Angle Angle::operator+( const Angle& right ) const
{
    Angle result = *this;
    result += right;
    return result;
}

Angle& Angle::operator-=( unsigned val )
{
    subtrackt( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator-=( int val )
{
    subtrackt( static_cast<double>( val ) );
    return *this;
}

Angle Angle::operator/( double val )
{
    Angle result( *this );
    result /= val;
    return result;
}

Angle Angle::operator/( int val )
{
    Angle result( *this );
    result /= val;
    return result;
}

Angle Angle::operator/( unsigned val )
{
    Angle result( *this );
    result /= val;
    return result;
}

Angle& Angle::operator/=( double value )
{
    divide( static_cast<double>( value ) );
    return *this;
}

Angle& Angle::operator/=( int val )
{
    divide( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator/=( unsigned val )
{
    divide( static_cast<double>( val ) );
    return *this;
}

void Angle::divide( double value )
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

Angle& Angle::operator*=( double val )
{
    multiply( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator*=( int val )
{
    multiply( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator*=( unsigned val )
{
    multiply( static_cast<double>( val ) );
    return *this;
}

void Angle::add( double value )
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

void Angle::subtrackt( double value )
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

void Angle::multiply( double value )
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

Angle Angle::operator*( double val )
{
    Angle result( *this );
    result *= val;
    return result;
}

Angle Angle::operator*( int val )
{
    Angle result( *this );
    result *= val;
    return result;
}

Angle Angle::operator*( unsigned val )
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

Angle& Angle::operator-=( double value )
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

void Angle::setValue( unsigned value, const Type type )
{
    setValue( static_cast<double>( value ), type );
}

void Angle::setValue( double value, const Type type )
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

void Angle::reset()
{
    m_valueRad = 0.0;
    m_valueDeg = 0.0;
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

float Angle::getRad() const
{
    return (float)m_valueRad;
}

float Angle::getDeg() const
{
    return (float)m_valueDeg;
}

double CUL::MATH::radian2degree( double radian )
{
    return radian * 180.0 / CUL::MATH::UTIL::Constants::PI;
}

double CUL::MATH::degree2radian( double degree )
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

Angle::~Angle()
{
}