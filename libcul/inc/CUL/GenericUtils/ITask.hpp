#pragma once

#include "CUL/UselessMacros.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class CULLib_API ITask
{
public:
    ITask() = default;
    virtual ~ITask() = default;

    virtual void execute() = 0;

protected:
private:
    ITask( const ITask& arg ) = delete;
    ITask& operator=( const ITask& rhv ) = delete;

};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )