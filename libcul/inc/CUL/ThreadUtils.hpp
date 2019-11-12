#pragma once

#include "CUL.hpp"
#include "CUL/MyString.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( ThreadUtils )

CULLib_API void setCurrentThreadName( CnstMyStr& name );

NAMESPACE_END( ThreadUtils )
NAMESPACE_END( CUL )