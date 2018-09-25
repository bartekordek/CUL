#pragma once

#include <CUL/CUL.hpp>
#include "CUL/MyString.hpp"

namespace CUL
{
    class CULLib_API Assert
    {
    public:
        static void simple( const bool val, CnstMyStr& msg = MyString( "" ) );
    protected:
    private:
    };
}