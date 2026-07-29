#pragma once

#include "CUL/GenericUtils/IArgumentsList.hpp"
#include "CUL/UselessMacros.hpp"
#include "CUL/GenericUtils/NonCopyable.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class ConsoleUtilities
{
public:
    CULLib_API static ConsoleUtilities& getInstance();

    CULLib_API void printInputParameters();
    CULLib_API IArgumentsList& getArgs();
    CULLib_API const String getFlagValue( const String& flagName ) const;
    CULLib_API const String getFlagValue( const String& flagName, const String& inFallbackValue ) const;    CULLib_API void setArgs( const int argc, char** argv );
    CULLib_API void setArgs( const char* args );
    CULLib_API bool getDoesFlagExist( const char* inFlagName ) const;

    CUL_NONCOPYABLE( ConsoleUtilities );

private:
    ConsoleUtilities();
    ~ConsoleUtilities();
    std::unique_ptr<IArgumentsList> m_args;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )