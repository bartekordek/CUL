#pragma once
#include <CUL/CUL.hpp>
namespace CUL
{
    class CULLib_API Assert
    {
    public:
        static void simple( const bool val, const char* msg = nullptr );
    protected:
    private:
    };
}