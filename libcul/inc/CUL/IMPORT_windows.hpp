#pragma once

#include "CUL/GenericUtils/DisableErros.hpp"
CUL_MSVC_SKIP_DEFAULT_WARNING_BEGIN
#if defined( _MSC_VER )
    #include <windows.h>
    #include <pdh.h>
    #include <pdhmsg.h>

    #undef ERROR
#endif  // #if defined(_MSC_VER)
CUL_MSVC_SKIP_DEFAULT_WARNING_END
