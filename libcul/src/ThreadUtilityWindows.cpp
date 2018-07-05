#include "ThreadUtilityWindows.hpp"

#pragma warning( push )  
#pragma warning( disable: 4668 5039 )  
#include <windows.h>
#pragma warning( pop )  

using namespace CUL;

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

ThreadUtilityWindows::ThreadUtilityWindows()
{

}

ThreadUtilityWindows::~ThreadUtilityWindows()
{

}

void ThreadUtilityWindows::setCurrentThreadName( CnstStr& name )
{
    DWORD dwID = GetCurrentThreadId();
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = name.c_str();
    info.dwThreadID = dwID;
    info.dwFlags = 0;

#pragma warning(push)  
#pragma warning(disable: 6320 6322)  
    __try {
        RaiseException( MS_VC_EXCEPTION, 0, sizeof( info ) / sizeof( ULONG_PTR ), (ULONG_PTR*)&info );
    }
    __except( EXCEPTION_EXECUTE_HANDLER ) {
    }
#pragma warning(pop)  
}