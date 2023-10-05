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

#if defined CUL_GLOBAL_MEMORY_POOL
#define CUL_GLOBAL_MEMORY_POOL 1
#else
#define CUL_GLOBAL_MEMORY_POOL 0
#endif // CUL_GLOBAL_MEMORY_POOL

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

#if defined( _MSC_VER)
#define CUL_COMPILER_MSVC
#elif defined( __GNUC__ ) || defined( __GNUG__ )
#define CUL_COMPILER_GCC
#elif defined( __clang__ )
#define CUL_COMPILER_CLANG
#else
#define CUL_COMPILER_UNKOWN
#endif

// Silly warnings removal.
#ifdef _MSC_VER
#pragma warning( disable : 4514 ) // unreferenced inline function has been removed
#endif