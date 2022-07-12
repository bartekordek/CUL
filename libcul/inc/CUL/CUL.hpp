#pragma once

#include "CUL/UselessMacros.hpp"

#if _WIN32
#define CUL_WINDOWS
#if defined CUL_STATIC
#define CUL_IMPORT
#else // CUL_STATIC
#define CUL_EXPORT
#endif //CUL_STATIC
#else // _WIN32
#define CUL_LINUX
#define CUL_EXPORT
#endif // _WIN32

#if defined CUL_MEMORY_POOL
#define CUL_MEMORY_POOL 1
#else
#define CUL_MEMORY_POOL 0
#endif // CUL_MEMORY_POOL

#if defined CUL_EXPORT && defined CUL_LINUX
#define CULLib_API
#define CULLib_API_POST
#define CULLib_API_TEMPLATE
#elif defined CUL_EXPORT && defined CUL_WINDOWS
#define CULLib_API __declspec(dllexport)
#define CULLib_API_POST __cdecl
#define CULLib_API_TEMPLATE
#else
#define CULLib_API
#define CULLib_API_POST
#define CULLib_API_TEMPLATE
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