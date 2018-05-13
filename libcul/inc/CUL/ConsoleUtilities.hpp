#pragma once

#include "CUL.hpp"

#include <utility>

namespace CUL
{
    struct CULLib_API ArgumentsPair
    {
        int argc = 0;
        char** argv = nullptr;
    };

    class CULLib_API ConsoleUtilities
    {
    public:
        static void printInputParameters( const ArgumentsPair& arguments );
        static ArgumentsPair& getDefaultArgs();

    private:
        static ArgumentsPair s_args;
    };
}