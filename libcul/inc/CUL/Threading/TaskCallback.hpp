#pragma once

#include "CUL/Threading/ITask.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN(CUL)

class CULLib_API TaskCallback final: public ITask
{
public:
    std::function<void( int8_t )> Callback;

    TaskCallback() = default;
    ~TaskCallback() = default;
    TaskCallback( const TaskCallback& ) = delete;
    TaskCallback( TaskCallback&& ) = delete;
    TaskCallback& operator=( const TaskCallback& ) = delete;
    TaskCallback& operator=( TaskCallback&& ) = delete;

    inline bool isDone() const override
    {
        return m_isDone;
    }

    inline void execute( int8_t workerId ) override
    {
        if( Callback )
        {
            Callback( workerId );
        }
        m_isDone = true;
    }

    inline void resetStatus() override
    {
        m_isDone = false;
    }

private:
    bool m_isDone = false;
};

NAMESPACE_END(CUL)