#pragma once

#include "ILogger.hpp"

#if CUL_RELEASE

    #define CUL_LOG( ... )
    #define CUL_LOG_INFO( ... )
    #define CUL_LOG_WARN( ... )
    #define CUL_LOG_ERROR( ... )
    #define CUL_LOG_CRITICAL( ... )

#else

    #define CUL_LOG( severity, ... )                                               \
        do                                                                         \
        {                                                                          \
            CUL::LOG::ILogger::getInstance().logVariable( severity, __VA_ARGS__ ); \
        } while( 0 )

    #define CUL_LOG_INFO( ... ) CUL_LOG( CUL::LOG::Severity::Info, __VA_ARGS__ )

    #define CUL_LOG_WARN( ... ) CUL_LOG( CUL::LOG::Severity::Warn, __VA_ARGS__ )

    #define CUL_LOG_ERROR( ... ) CUL_LOG( CUL::LOG::Severity::Error, __VA_ARGS__ )

    #define CUL_LOG_CRITICAL( ... ) CUL_LOG( CUL::LOG::Severity::Critical, __VA_ARGS__ )

#endif