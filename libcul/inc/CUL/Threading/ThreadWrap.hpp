#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )

class ThreadWrapper final
{
public:
    CULLib_API ThreadWrapper( std::function<void( void )> threadBody );

    CULLib_API void run();
    CULLib_API void waitForCompletion();

    CULLib_API ~ThreadWrapper();

protected:
private:
    std::thread m_mainThread;
    std::function<void( void )> m_body;

//Deleted:
    ThreadWrapper( const ThreadWrapper& value ) = delete;
    ThreadWrapper( ThreadWrapper&& value ) = delete;
    ThreadWrapper& operator=( const ThreadWrapper& value ) = delete;
    ThreadWrapper& operator=( ThreadWrapper&& value ) = delete;
};

NAMESPACE_END( CUL )