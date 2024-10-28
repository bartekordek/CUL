#pragma once

#include "CUL/GenericUtils/DisableErros.hpp"

#if defined( _MSC_VER )
#include <windows.h>
#undef ERROR
#endif  // #if defined(_MSC_VER)

#ifdef _MSC_VER
#pragma warning( pop )
#endif