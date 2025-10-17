#pragma once

#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

#include "CUL/GenericUtils/DisableErros.hpp"
CUL_MSVC_SKIP_DEFAULT_WARNING_BEGIN

#if defined( CUL_WINDOWS ) && !CUL_WINDOWS_CLANG && CUL_PROFILER_PIX
typedef unsigned int UINT;
typedef unsigned char BYTE;
using UINT64 = std::uint64_t;
using PCWSTR = const wchar_t*;
using PCSTR = const char*;
#include <pix.h>
#endif  // #if !CUL_WINDOWS_CLANG
CUL_MSVC_SKIP_DEFAULT_WARNING_END