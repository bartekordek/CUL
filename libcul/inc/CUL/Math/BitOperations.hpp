#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( MATH )

using BinaryDigitType = unsigned char;
template <typename Type>
std::vector<BinaryDigitType> toBin( const Type val )
{
    auto sizeOfType = sizeof( val ) * 8;
    std::vector<BinaryDigitType> result;
    result.resize( sizeOfType );
    int tempDigit = 0;
    int digit = 0;
    for( unsigned long i = 0; i < sizeOfType; ++i )
    {
        tempDigit = val >> i;
        digit = tempDigit & 1;
        result[ i ] = digit;
    }
    return result;
}


NAMESPACE_END( MATH )
NAMESPACE_END( CUL )