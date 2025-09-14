
#pragma once

#if defined( CUL_WINDOWS )
    #include "CUL/GenericUtils/DisableErros.hpp"
CUL_MSVC_SKIP_DEFAULT_WARNING_BEGIN
    // #include "stringapiset.h"
    #include <windows.h>
CUL_MSVC_SKIP_DEFAULT_WARNING_END
#endif  // #if defined(CUL_WINDOWS)