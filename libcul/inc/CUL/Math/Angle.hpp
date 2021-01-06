#pragma once

#include "CUL/CUL.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

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
    Angle( Cdouble value, const Type type = Type::RADIAN );
    Angle( Cint value, const Type type = Type::RADIAN );

    double getValueD( const Type type = Type::RADIAN ) const;
    float getValueF( const Type type = Type::RADIAN ) const;
    int getValueI( const Type type = Type::RADIAN ) const;

    void setValue( Cdouble value, const Type type = Type::RADIAN );
    void setValue( Cunt value, const Type type = Type::RADIAN );
    void setValue( Cint value, const Type type = Type::RADIAN );

    void setIncrementValue( Cunt value );
    void setIncrementValue( Cint value );
    void setIncrementValue( Cdouble value );

    Type getCurrentType() const;
    void setCurrentType( const Type type );

    Angle& operator+=( Cunt val );
    Angle& operator+=( Cint val );
    Angle& operator+=( Cdouble val );

    Angle& operator-=( Cunt val );
    Angle& operator-=( Cint val );
    Angle& operator-=( Cdouble val );

    Angle operator/( Cdouble val );
    Angle operator/( Cint val );
    Angle operator/( Cunt val );

    Angle& operator/=( Cdouble val );
    Angle& operator/=( Cint val );
    Angle& operator/=( Cunt val );

    Angle& operator*=( Cdouble val );
    Angle& operator*=( Cint val );
    Angle& operator*=( Cunt val );

    Angle operator*( Cdouble val );
    Angle operator*( Cint val );
    Angle operator*( Cunt val );

    Angle& operator++();
    Angle& operator--();

    Angle operator++( int );
    Angle operator--( int );

    operator double() const;
    operator int() const;

    virtual ~Angle();

protected:
private:
    void add( Cdouble value );
    void subtrackt( Cdouble value );
    void multiply( Cdouble value );
    void divide( Cdouble value );
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
CULLib_API double radian2degree( Cdouble radian );
CULLib_API double degree2radian( Cdouble degree );

CULLib_API float radian2degree( Cfloat radian );
CULLib_API float degree2radian( Cfloat degree );

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )