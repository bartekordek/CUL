#pragma once

#include "CUL/String.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_unordered_map.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include <CUL/GenericUtils/NonCopyable.hpp>
#include "CUL/IMPORT_windows.hpp"

namespace CUL
{
struct Argument
{
    String Name;
    String Value;
    std::int32_t Index{0};
};

class CommandlineParser final
{
public:
    CULLib_API static CommandlineParser& getInstance();

    CULLib_API void passVariables( const std::int32_t argc, char** argv );
    CULLib_API const String getArgument( std::size_t inArg ) const;
    CULLib_API const String getFlagValue( const String& inFlagName ) const;
    CULLib_API const String& getExecutablePath() const;
    CULLib_API const String& getAppName() const;
#if defined( CUL_WINDOWS )
    CULLib_API void passWindowsVariables( HINSTANCE inInst, PSTR cmd );
#endif // #if defined(CUL_WINDOWS)

protected:
private:
    CommandlineParser();
    ~CommandlineParser();

private:
    std::unordered_map<std::string, Argument> m_values;

public:
    CUL_NONCOPYABLE( CommandlineParser )
};
}  // namespace CUL