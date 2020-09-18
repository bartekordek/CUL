#pragma once

#include "CUL/STL_IMPORTS/STD_string.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

template< typename T >
std::string intToHex( T i )
{
    std::stringstream stream;
    stream << "0x"
        << std::setfill( '0' ) << std::setw( sizeof( T ) * 2 )
        << std::hex << i;
    return stream.str();
}

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )