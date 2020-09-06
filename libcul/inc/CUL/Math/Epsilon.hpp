#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/Math/Math.hpp"
#include "CUL/STL_IMPORTS/STD_type_traits.hpp"
#include "CUL/STL_IMPORTS/STD_cmath.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif
template <typename Type>
class Epsilon
{
public:
    Epsilon()
    {
        bool isFloatPoint = std::is_same<Type, float>::value || std::is_same<Type, double>::value;
        if( isFloatPoint )
        {
            epsilon = static_cast<Type>( 0.0000000001 );
        }
    }

    virtual ~Epsilon() = default;

    void setEpsilon( const double epislon )
    {
        epsilon = epislon;
    }

    const Type getEpsilon() const
    {
        return epsilon;
    }

    template <typename SomeOtherType>
    bool isLessThanEpislon( const SomeOtherType value ) const
    {
        return std::abs( value ) < getEpsilon();
    }

protected:
    bool equals( const Type val1, const Type val2 ) const
    {
        const Type epsilonAsType = static_cast<Type>( epsilon );
        return std::abs( val1 - val2 ) <= epsilonAsType;
    }
private:
    Type epsilon = static_cast<Type>( 0 );
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( MATH )
NAMESPACE_END( CUL )