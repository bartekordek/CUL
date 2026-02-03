#include "CUL/String/IString.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_source_location.hpp"

namespace CUL
{
bool IString::operator==( const char* inArg ) const
{
    return equals( inArg );
}

bool IString::startsWith( const char* inArg ) const
{
    const char* name = __func__;
    Assert::check( false, "NOT IMPLEMENTED: %s", name );
    return false;
}

bool IString::startsWith( const wchar_t* inArg ) const
{
    const char* name = __func__;
    Assert::check( false, "NOT IMPLEMENTED: %s", name );
    return false;
}

bool IString::isFloat() const
{
    const char* name = __func__;
    Assert::check( false, "NOT IMPLEMENTED: %s", name );

    return false;
}

float IString::toFloat() const
{
    const char* name = __func__;
    Assert::check( false, "NOT IMPLEMENTED: %s", name );

    return 0.f;
}

std::int64_t IString::toInt64() const
{
    const char* name = __func__;
    Assert::check( false, "NOT IMPLEMENTED: %s", name );

    return 0;
}
std::u8string IString::toU8String() const
{
    const char* name = __func__;
    Assert::check( false, "NOT IMPLEMENTED: %s", name );
    return std::u8string();
}
}
