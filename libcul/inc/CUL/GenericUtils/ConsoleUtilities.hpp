#pragma once
#include "CUL/GenericUtils/IArgumentsPair.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class ConsoleUtilities
{
public:
    CULLib_API void printInputParameters();
    CULLib_API IArgumentsPair& getDefaultArgs();
    CULLib_API void setArgs( const int argc, char** argv );

    CULLib_API static ConsoleUtilities& getInstance();

    CULLib_API ConsoleUtilities( const ConsoleUtilities & ) = delete;
    CULLib_API ConsoleUtilities& operator=( const ConsoleUtilities & ) = delete;

private:
    CULLib_API ConsoleUtilities();
    CULLib_API ~ConsoleUtilities();

    std::unique_ptr<IArgumentsPair> m_args;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )