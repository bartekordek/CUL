#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

enum class EulerAngles: uint8_t
{
    YAW = 0, // X-Y [Z]
    PITCH,   // X-Z [Y]
    ROLL     // Y-Z [X]
};

class CULLib_API Angle
{
public:
    enum class Type: short
    {
        DEGREE,
        RADIAN
    };

    Angle();
    Angle( double value, const Type type );
    Angle( int value, const Type type  );

    void reset();

    double getValueD( const Type type ) const;
    float getValueF( const Type type  ) const;
    int getValueI( const Type type ) const;

    void setValue( double value, const Type type);
    void setValue( unsigned value, const Type type );
    void setValue( int value, const Type type);

    void setIncrementValue( unsigned value );
    void setIncrementValue( int value );
    void setIncrementValue( double value );

    float getRad() const;
    float getDeg() const;

    Type getCurrentType() const;
    void setCurrentType( const Type type );

    Angle& operator=( float value );

    Angle& operator+=( const Angle& right );
    Angle& operator-=( const Angle& right );


    Angle& operator+=( unsigned val );
    Angle& operator+=( int val );
    Angle& operator+=( double val );

    Angle operator+( const Angle& right ) const;

    Angle& operator-=( unsigned val );
    Angle& operator-=( int val );
    Angle& operator-=( double val );

    Angle operator/( double val );
    Angle operator/( int val );
    Angle operator/( unsigned val );

    Angle& operator/=( double val );
    Angle& operator/=( int val );
    Angle& operator/=( unsigned val );

    Angle& operator*=( double val );
    Angle& operator*=( int val );
    Angle& operator*=( unsigned val );

    Angle operator*( double val );
    Angle operator*( int val );
    Angle operator*( unsigned val );

    Angle& operator++();
    Angle& operator--();

    Angle operator++( int );
    Angle operator--( int );

    virtual ~Angle();

protected:
private:
    void add( double value );
    void subtrackt( double value );
    void multiply( double value );
    void divide( double value );
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
CULLib_API double radian2degree( double radian );
CULLib_API double degree2radian( double degree );

CULLib_API float radian2degree( float radian );
CULLib_API float degree2radian( float degree );

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )