#include "CUL/Math/Angle.hpp"
#include "CUL/Math/Math.hpp"

using Angle = CUL::Math::Angle;
using Type = CUL::Math::Angle::Type;

Angle::Angle()
{

}

Angle::Angle( const double value, const Type type )
{
    setValue( value, type );
}

Angle::Angle( const int value, const Type type )
{
    setValue( value, type );
}

Angle::~Angle()
{

}

const int Angle::getValueI( const Type type ) const
{
    return static_cast< int >( getValueD( type ) );
}

void Angle::setValue( const int value, const Type type )
{
    setValue( static_cast<double>( value ), type );
}

void Angle::setIncrementValue( const unsigned int value )
{
    setIncrementValue( static_cast<double>( value ) );
}

void Angle::setIncrementValue( const int value )
{
    setIncrementValue( static_cast<double>( value ) );
}

void Angle::setIncrementValue( const double value )
{
    m_incrementValue = value;
}

const Type Angle::getCurrentType() const
{
    return m_type;
}

void Angle::setCurrentType( const Type type )
{
    m_type = type;
}

Angle& Angle::operator+=( const unsigned int val )
{
    add( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator+=( const int val )
{
    add( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator+=( const double value )
{
    add( value );
    return *this;
}

Angle& Angle::operator-=( const unsigned int val )
{
    subtrackt( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator-=( const int val )
{
    subtrackt( static_cast<double>( val ) );
    return *this;
}

Angle Angle::operator/( const double val )
{
    Angle result( *this );
    result /= val;
    return result;
}

Angle Angle::operator/( const int val )
{
    Angle result( *this );
    result /= val;
    return result;
}

Angle Angle::operator/( const unsigned int val )
{
    Angle result( *this );
    result /= val;
    return result;
}

Angle& Angle::operator/=( const double value )
{
    divide( static_cast<double>( value ) );
    return *this;
}

Angle& Angle::operator/=( const int val )
{
    divide( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator/=( const unsigned int val )
{
    divide( static_cast<double>( val ) );
    return *this;
}

void Angle::divide( const double value )
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

Angle& Angle::operator*=( const double val )
{
    multiply( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator*=( const int val )
{
    multiply( static_cast<double>( val ) );
    return *this;
}

Angle& Angle::operator*=( const unsigned int val )
{
    multiply( static_cast<double>( val ) );
    return *this;
}

void Angle::add( const double value )
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

void Angle::subtrackt( const double value )
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

void Angle::multiply( const double value )
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

Angle Angle::operator*( const double val )
{
    Angle result( *this );
    result *= val;
    return result;
}

Angle Angle::operator*( const int val )
{
    Angle result( *this );
    result *= val;
    return result;
}

Angle Angle::operator*( const unsigned int val )
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

Angle& Angle::operator-=( const double value )
{
    if( Type::RADIAN == this->m_type )
    {
        this->m_valueRad -= value;
        this->m_valueDeg = radian2degree( this->m_valueRad );
    }
    else
    {
        this->m_valueDeg -= value;
        this->m_valueRad = degree2radian( this->m_valueDeg );
    }
    return *this;
}

void Angle::setValue( const unsigned int value, const Type type )
{
    setValue( static_cast<double>( value ), type );
}

void Angle::setValue( const double value, const Type type )
{
    if( Type::RADIAN == type )
    {
        this->m_valueRad = value;
        this->m_valueDeg = radian2degree( value );
    }
    else
    {
        this->m_valueDeg = value;
        this->m_valueRad = degree2radian( value );
    }
    m_type = type;
}

const double Angle::getValueD( const Type type ) const
{
    if( Type::RADIAN == type )
    {
        return this->m_valueRad;
    }
    return this->m_valueDeg;
}

const float Angle::getValueF(const Type type) const
{
    if (Type::RADIAN == type)
    {
        return static_cast<float>( this->m_valueRad );
    }
    return static_cast<float>( this->m_valueDeg );
}


// ASUMPTION!
// We are returning radian.
// Why? Mostly, if people want Degrees, they want them to be integer.
Angle::operator const double() const
{
    return m_valueRad;
}

Angle::operator const int() const
{
    return m_valueDeg;
}

const double CUL::Math::radian2degree( const double radian )
{
    return radian * 180.0 / CUL::Math::Util::Constants::PI;
}

const double CUL::Math::degree2radian( const double degree )
{
    return degree * CUL::Math::Util::Constants::PI / 180.0;
}

const float CUL::Math::radian2degree( const float radian )
{
	return radian * 180.0f / static_cast<float>( CUL::Math::Util::Constants::PI );
}

const float CUL::Math::degree2radian( const float degree )
{
	return degree * CUL::Math::Util::Constants::PI / 180.0f;
}