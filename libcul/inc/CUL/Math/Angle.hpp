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
    Angle( Cdouble value, const Type type = Type::RADIAN );
    Angle( Cint value, const Type type = Type::RADIAN );
    virtual ~Angle();

    Cdouble getValueD( const Type type = Type::RADIAN ) const;
    Cfloat getValueF(const Type type = Type::RADIAN) const;
    Cint getValueI( const Type type = Type::RADIAN ) const;

    void setValue( Cdouble value, const Type type = Type::RADIAN );
    void setValue( Cunt value, const Type type = Type::RADIAN );
    void setValue( Cint value, const Type type = Type::RADIAN );

    void setIncrementValue( Cunt value );
    void setIncrementValue( Cint value );
    void setIncrementValue( Cdouble value );

    const Type getCurrentType() const;
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

    operator Cdouble() const;
    operator Cint() const;

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
CULLib_API Cdouble radian2degree( Cdouble radian );
CULLib_API Cdouble degree2radian( Cdouble degree );

CULLib_API Cfloat radian2degree( Cfloat radian );
CULLib_API Cfloat degree2radian( Cfloat degree );

NAMESPACE_END( Math )
NAMESPACE_END( CUL )