#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )

#if defined(CUL_PROFILER_PIX)
#else
    #define CUL_PROFILER_PIX 0
#endif

class Profiler final
{
public:
    Profiler(const char* eventName);
    ~Profiler();
protected:
private:
};

NAMESPACE_END(CUL)