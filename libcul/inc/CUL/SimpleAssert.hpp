#pragma once

#include <CUL/CUL.hpp>
#include "CUL/STD_string.hpp"

namespace CUL
{
    class CULLib_API Assert
    {
    public:
        static void simple( const bool val, const std::string& msg = std::string( "" ) );
    protected:
    private:
    };
}