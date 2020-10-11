#pragma once

#include "CUL.hpp"
#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( ThreadUtils )

CULLib_API void setCurrentThreadName( const String& name );

NAMESPACE_END( ThreadUtils )
NAMESPACE_END( CUL )