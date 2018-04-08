#pragma once


#include <CUL/CUL.hpp>

#include <string>

namespace CUL
{
    class CULLib_API Assert
    {
    public:
        static void simple( const bool val, const std::string& msg = std::string( "" ) );
        static void simple( const bool val, const char* msg = nullptr );
    protected:
    private:
    };
}