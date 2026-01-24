#include "CUL/String/IString.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_source_location.hpp"

namespace CUL
{
bool IString::operator==( const char* inArg ) const
{
    return equals( inArg );
}
}
