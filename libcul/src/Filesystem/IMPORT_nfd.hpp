#pragma once

#include "CUL/GenericUtils/DisableErros.hpp"
CUL_MSVC_SKIP_DEFAULT_WARNING_BEGIN
#define NFD_NATIVE
#include "nfd.h"

#ifdef _MSC_VER
#pragma warning( pop )
#endif