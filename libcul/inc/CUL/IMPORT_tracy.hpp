#pragma once

#include "CUL/GenericUtils/DisableErros.hpp"
CUL_MSVC_SKIP_DEFAULT_WARNING_BEGIN
#if defined( TRACY_ENABLE )
    // #include "tracy/TracyC.h"
    #include "tracy/Tracy.hpp"
// TODO: skip for now
// #pragma message( "Including tracy." )
#endif  // TRACY_ENABLE
CUL_MSVC_SKIP_DEFAULT_WARNING_END
