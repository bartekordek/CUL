#pragma once

#include "CUL/GenericUtils/IArgumentsList.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class ConsoleUtilities
{
public:
    CULLib_API ConsoleUtilities();

    CULLib_API void printInputParameters();
    CULLib_API IArgumentsList& getArgs();
    CULLib_API const String& getFlagValue( const String& flagName ) const;
    CULLib_API void setArgs( const int argc, char** argv );

    CULLib_API ~ConsoleUtilities();

private:
    CULLib_API ConsoleUtilities( const ConsoleUtilities& ) = delete;
    CULLib_API ConsoleUtilities( ConsoleUtilities&& ) = delete;
    CULLib_API ConsoleUtilities& operator=( const ConsoleUtilities& ) = delete;
    CULLib_API ConsoleUtilities& operator=( ConsoleUtilities&& ) = delete;

    std::unique_ptr<IArgumentsList> m_args;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )
