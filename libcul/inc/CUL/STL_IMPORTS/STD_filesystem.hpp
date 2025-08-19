#pragma once

#include "CUL/GenericUtils/DisableErros.hpp"
CUL_MSVC_SKIP_DEFAULT_WARNING_BEGIN
#if defined( _MSC_VER ) && _MSC_VER < 1920
    #include <experimental/filesystem>
    #define FILESYSTEM_IS_EXPERIMENTAL
#else
    #include <filesystem>
#endif
CUL_MSVC_SKIP_DEFAULT_WARNING_END
