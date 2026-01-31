#pragma once

#include "CUL/String/String.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"

NAMESPACE_BEGIN( CUL )

#undef Status

struct ThreadMeta
{
    std::string Name;
    std::string Status;
    std::thread::id ID;
};

NAMESPACE_END( CUL )