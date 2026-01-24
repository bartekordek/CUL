#pragma once

#ifdef _WIN32 //compile only on windows.
#include "CUL/String/String.hpp"

void setCurrentThreadNameWin( const CUL::String& name );
#endif // _WIN32 //compile only on windows.