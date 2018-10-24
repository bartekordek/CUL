#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STD_string.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API Assert
{
public:
    static void simple( const bool val, const std::string& msg = std::string( "" ) );
protected:
private:
};

NAMESPACE_END( CUL )