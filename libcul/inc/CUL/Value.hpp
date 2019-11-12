#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
class CULLib_API Value
{
public:
    Value( void );
    Value( const Value& valueIn );
    virtual ~Value( void );

    Value& operator=( const double valueIn );
    Value operator*( const Value& rhv );
    Value& operator*=( const Value& rhv );
    Value operator+( const Value& rhv );
    Value& operator+=( const Value& rhv );
    Value operator-( const Value& rhv );
    Value& operator-=( const Value& rhv );
    Value operator/( const Value& rhv );
    Value& operator/=( const Value& rhv );

    const double getValue( void )const;
    const bool toBeCalculated( void )const;

protected:
private:
    double m_value = 0.0;
    bool m_toBeCalculated = true;

};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( CUL )