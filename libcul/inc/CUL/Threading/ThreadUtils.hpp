#pragma once

#include "CUL/String.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"


NAMESPACE_BEGIN( CUL )


class ThreadUtils final
{
public:
    ThreadUtils();

    CULLib_API void setCurrentThreadName( const String& name );
    CULLib_API const String& getCurrentThreadName();
    CULLib_API bool getIsCurrentThreadNameEqualTo( const String& name );

    ~ThreadUtils();
protected:
private:
    std::map<String,std::thread::id> m_threadMaps;
    String m_emptyname = "UNKOWN THREAD";


    ThreadUtils& operator=( const ThreadUtils& rhv ) = delete;
    ThreadUtils& operator=( ThreadUtils&& rhv ) = delete;
    ThreadUtils( const ThreadUtils& arg ) = delete;
    ThreadUtils( ThreadUtils&& arg ) = delete;
};


NAMESPACE_END( CUL )