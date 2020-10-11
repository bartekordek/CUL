#pragma once

#include "CUL/String.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( ThreadUtils )

void setCurrentThreadNameWin( const String& name );

NAMESPACE_END( ThreadUtils )
NAMESPACE_END( CUL )