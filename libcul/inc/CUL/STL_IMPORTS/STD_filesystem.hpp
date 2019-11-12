#pragma once

#include "CUL/GenericUtils/DisableErros.hpp"

#if defined( _MSC_VER )
    #if _MSC_VER < 1920
        #include <experimental/filesystem>
        #define FILESYSTEM_IS_EXPERIMENTAL
    #else
    #include <filesystem>
    #endif
#elif defined( __GNUC__ ) || defined( __clang__ )
    #include <experimental/filesystem>
    #define FILESYSTEM_IS_EXPERIMENTAL
#else
    #include <filesystem>
#endif

#ifdef _MSC_VER
#pragma warning( pop )
#endif