#include "ThreadUtilityWindows.hpp"
#ifdef _WIN32 //compile only on windows.
#include "GUARD_windows.hpp"

const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma warning( push )
#pragma warning( disable: 4820 )
typedef struct tagTHREADNAME_INFO
{
    DWORD dwType; // Must be 0x1000.
    LPCSTR szName; // Pointer to name (in user addr space).
    DWORD dwThreadID; // Thread ID (-1=caller thread).
    DWORD dwFlags; // Reserved for future use, must be zero.
} THREADNAME_INFO;
#pragma warning( pop )

void setCurrentThreadNameWin( const CUL::String& name )
{
    DWORD dwID = GetCurrentThreadId();
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = name.cStr();
    info.dwThreadID = dwID;
    info.dwFlags = 0;

#pragma warning(push)
#pragma warning(disable: 6320 6322)
    __try
    {
        RaiseException( MS_VC_EXCEPTION, 0, sizeof( info ) / sizeof( ULONG_PTR ), (ULONG_PTR*) &info );
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
    }
#pragma warning(pop)
}
#endif