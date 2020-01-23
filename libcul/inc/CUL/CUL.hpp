#pragma once

#include "CUL/UselessMacros.hpp"

#if _WIN32
#define CUL_WINDOWS
#define CUL_EXPORT
#else
#define CUL_LINUX
#define CUL_EXPORT
#endif

#if defined CUL_EXPORT && defined CUL_LINUX
#define CULLib_API
#define CULLib_API_POST
#define CULLib_API_TEMPLATE
#elif defined CUL_EXPORT && defined CUL_WINDOWS
#define CULLib_API __declspec(dllexport)
#define CULLib_API_POST __cdecl
#define CULLib_API_TEMPLATE
#else
#define CULLib_API __declspec(dllimport)
#define CULLib_API_POST __cdecl
#define CULLib_API_TEMPLATE extern
#endif
/*TODO: Find a way to tell library name.
#if defined _MSC_VER && defined CUL_DYNAMIC
#pragma comment(lib, "CULdynamic.lib")
#elif _MSC_VER
#pragma comment(lib, "CULstatic.lib")
#else
#pragma comment(lib, "libcul.a")
#endif
*/

NAMESPACE_BEGIN( CUL )

using Cbool = const bool;
using Cunt = const unsigned int;
using Cint = const int;
using Cdouble = const double;
using Cfloat = const float;
using Cint64 = const long int;

NAMESPACE_END( CUL )