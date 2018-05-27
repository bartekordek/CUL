#pragma once
#include "CUL/IArgumentsPair.hpp"
#pragma warning( push, 0 ) // Disable all dependency header warnings.
#pragma warning( disable: 4365 )
#pragma warning( disable: 4514 )
#include <memory>
#pragma warning( pop )
namespace CUL
{
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
}