#include "CUL/Value.hpp"

using namespace CUL;

Value::Value( void )
{

}

Value::Value( const Value& valueIn ):
    m_value( valueIn.m_value ),
    m_toBeCalculated( valueIn.m_toBeCalculated )
{

}

Value::~Value( void )
{
}

Value& Value::operator=( const double valueIn )
{
    m_value = valueIn;
    m_toBeCalculated = false;
    return *this;
}

Value Value::operator*( const Value& rhv )
{
    Value result( *this );
    result *= rhv;
    result.m_toBeCalculated = false;
    return result;
}

Value Value::operator+( const Value& rhv )
{
    Value result( *this );
    result += rhv;
    result.m_toBeCalculated = false;
    return result;
}

Value& Value::operator+=( const Value& rhv )
{
    m_value += rhv.m_value;
    return *this;
}

Value& Value::operator*=( const Value& rhv )
{
    m_value *= rhv.m_value;
    return *this;
}

Value Value::operator-( const Value& rhv )
{
    Value result( *this );
    result -= rhv;
    result.m_toBeCalculated = false;
    return result;
}

Value& Value::operator-=( const Value& rhv )
{
    m_value -= rhv.m_value;
    return *this;
}

Value Value::operator/( const Value& rhv )
{
    Value result( *this );
    result /= rhv;
    result.m_toBeCalculated = false;
    return result;
}

Value& Value::operator/=( const Value& rhv )
{
    m_value /= rhv.m_value;
    return *this;
}

const double Value::getValue( void ) const
{
    return m_value;
}

const bool Value::toBeCalculated( void ) const
{
    return m_toBeCalculated;
}