#pragma once

#include "CUL/GenericUtils/DisableErros.hpp"
CUL_MSVC_SKIP_DEFAULT_WARNING_BEGIN
#if defined( TRACY_ENABLE )
#include "tracy/Tracy.hpp"
#else
#define ZoneScoped
#define FrameMark
#endif  // TRACY_ENABLE
CUL_MSVC_SKIP_DEFAULT_WARNING_END
