#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API ITask
{
public:
    bool DeleteAfterCompletion = false;
    int8_t OnlyForWorkerOfId = -1; // if set to -1, then any worker can execute task.

    virtual bool isDone() const = 0;
    virtual void execute( int8_t workerId ) = 0;
    std::function<void(int8_t)> AfterExecutionCallback;

    ITask() = default;
    virtual ~ITask() = default;
    ITask( const ITask& ) = delete;
    ITask( ITask&& ) = delete;
    ITask& operator=( const ITask& ) = delete;
    ITask& operator=( ITask&& ) = delete;

protected:
private:
};

NAMESPACE_END( CUL )