#pragma once

#include "CUL/String.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_optional.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"

NAMESPACE_BEGIN( CUL )

#undef Status

class ThreadUtil final
{
public:
    CULLib_API ThreadUtil();

    CULLib_API static ThreadUtil& getInstance();

    CULLib_API const std::thread::id getCurrentThreadId() const;
    CULLib_API void setThreadName( const String& name, const std::thread::id* threadId = nullptr );
    CULLib_API void setThreadStatus( const String& name, const std::thread::id* threadId = nullptr );
    CULLib_API String getThreadName( const std::thread::id* threadId = nullptr ) const;
    CULLib_API String getThreadStatus( const std::thread::id* threadId = nullptr ) const;
    CULLib_API std::vector<String> getThreadNames() const;
    CULLib_API bool getIsCurrentThreadNameEqualTo( const String& name ) const;
    CULLib_API void sleepFor( uint16_t ms );

    CULLib_API ~ThreadUtil();

protected:
private:
    struct ThreadInfo
    {
        String Name;
        String Status;
    };

    std::map<std::thread::id, ThreadInfo> m_threadInfo;
    mutable std::mutex m_threadInfoMtx;

    ThreadUtil& operator=( const ThreadUtil& rhv ) = delete;
    ThreadUtil& operator=( ThreadUtil&& rhv ) = delete;
    ThreadUtil( const ThreadUtil& arg ) = delete;
    ThreadUtil( ThreadUtil&& arg ) = delete;
};
NAMESPACE_END( CUL )