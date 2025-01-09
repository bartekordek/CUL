#pragma once

#include "CUL/String.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"

NAMESPACE_BEGIN( CUL )

#undef Status

struct ThreadMeta
{
    String Name;
    String Status;
    std::thread::id ID;
};

NAMESPACE_END( CUL )