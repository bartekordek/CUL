#pragma once

#include "CUL/String.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

namespace CUL
{
struct Argument
{
    String
};

class CommandlineParser final
{
public:
    CUL_NONCOPYABLE( CommandlineParser )

    CULLib_API void passVariables( const std::int32_t argc, const char** argv );
    CULLib_API const String& getArgument( std::size_t inArg ) const;

protected:
private:
    CommandlineParser();
    ~CommandlineParser();

private:
};
}  // namespace CUL