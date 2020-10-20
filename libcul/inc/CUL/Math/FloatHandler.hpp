#pragma once

#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_type_traits.hpp"

template <typename Type>
class FloatHandler
{
    static_assert(std::is_same<float, Type>::value || std::is_same<double, Type>::value, "Type must inherit from float or double");
public:
    FloatHandler()
    {

    }

    FloatHandler( const Type someValue ):
        value( someValue )
    {

    }

    FloatHandler( const FloatHandler<Type>& arg ):
        value( arg.value ),
        epsilon( arg.epsilon )
    {

    }

    FloatHandler& operator=( const FloatHandler<Type>& arg )
    {
        if( this != &arg )
        {
            value = arg.value;
            epsilon = arg.epsilon;
        }
        return *this;
    }

    operator const Type() const
    {
        return value;
    }

    const bool operator==( const FloatHandler<Type>& arg ) const
    {
        return std::abs( value - arg.value ) <= epsilon;
    }

    const bool operator==( const Type arg ) const
    {
        return std::abs( value - arg ) <= epsilon;
    }

    const bool operator<( const FloatHandler<Type>& arg ) const
    {
        return value < arg.value;
    }

    const bool operator<( const Type arg )const
    {
        return value < arg;
    }

    Type value = static_cast<Type>( 0.0 );
    Type epsilon = static_cast<Type>( 0.0001 );

protected:
private:
    // Deleted:
    FloatHandler& operator=( FloatHandler<Type>&& arg ) = delete;
    FloatHandler( FloatHandler<Type>&& arg ) = delete;
};