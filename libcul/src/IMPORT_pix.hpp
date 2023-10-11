#pragma once

#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

#include "CUL/GenericUtils/DisableErros.hpp"

#ifdef _MSC_VER
typedef unsigned int UINT;
typedef unsigned char BYTE;
using UINT64 = std::uint64_t;
using PCWSTR = const wchar_t*;
using PCSTR = const char*;
#include <pix.h>

#pragma warning( pop )
#endif