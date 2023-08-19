#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )

class CULLib_API ITask
{
public:
    bool DeleteAfterCompletion = false;

    virtual void isDone() const = 0;
    virtual void execute() = 0;
    std::function<void(void)> AfterExecutionCallback;

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