#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Math )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
class CULLib_API Angle
{
public:
    enum class Type: short
    {
        DEGREE,
        RADIAN
    };

    Angle();
    Angle( const double value, const Type type = Type::RADIAN );
    Angle( const int value, const Type type = Type::RADIAN );
    virtual ~Angle();

    const double getValueD( const Type type = Type::RADIAN ) const;
    const float getValueF(const Type type = Type::RADIAN) const;
    const int getValueI( const Type type = Type::RADIAN ) const;

    void setValue( const double value, const Type type = Type::RADIAN );
    void setValue( const unsigned int value, const Type type = Type::RADIAN );
    void setValue( const int value, const Type type = Type::RADIAN );

    void setIncrementValue( const unsigned int value );
    void setIncrementValue( const int value );
    void setIncrementValue( const double value );

    const Type getCurrentType() const;
    void setCurrentType( const Type type );

    Angle& operator+=( const unsigned int val );
    Angle& operator+=( const int val );
    Angle& operator+=( const double val );

    Angle& operator-=( const unsigned int val );
    Angle& operator-=( const int val );
    Angle& operator-=( const double val );

    Angle operator/( const double val );
    Angle operator/( const int val );
    Angle operator/( const unsigned int val );

    Angle& operator/=( const double val );
    Angle& operator/=( const int val );
    Angle& operator/=( const unsigned int val );

    Angle& operator*=( const double val );
    Angle& operator*=( const int val );
    Angle& operator*=( const unsigned int val );

    Angle operator*( const double val );
    Angle operator*( const int val );
    Angle operator*( const unsigned int val );

    Angle& operator++();
    Angle& operator--();

    Angle operator++( int );
    Angle operator--( int );

    operator const double() const;
    operator const int() const;

protected:
private:
    void add( const double value );
    void subtrackt( const double value );
    void multiply( const double value );
    void divide( const double value );
    void increment();
    void decrement();

    double m_valueRad = 0.0;
    double m_valueDeg = 0.0;
    double m_incrementValue = 0.1;
    Type m_type = Type::RADIAN;

};
#ifdef _MSC_VER
#pragma warning( pop )
#endif
CULLib_API const double radian2degree( const double radian );
CULLib_API const double degree2radian( const double degree );

CULLib_API const float radian2degree( const float radian );
CULLib_API const float degree2radian( const float degree );

NAMESPACE_END( Math )
NAMESPACE_END( CUL )