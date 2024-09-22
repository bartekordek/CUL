#pragma once

#include "CUL/Threading/ThreadMeta.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

NAMESPACE_BEGIN( CUL )

struct ThreadMeta;

class CULLib_API CThreadUtilObserver
{
public:
    CThreadUtilObserver() = default;
    CThreadUtilObserver( const CThreadUtilObserver& ) = delete;
    CThreadUtilObserver( CThreadUtilObserver&& ) = delete;
    CThreadUtilObserver& operator=( const CThreadUtilObserver& ) = delete;
    CThreadUtilObserver& operator=( CThreadUtilObserver&& ) = delete;

    virtual void onThreadsStateUpdated( const std::vector<ThreadMeta>& ti ) = 0;

    virtual ~CThreadUtilObserver() = default;

protected:
private:
};


NAMESPACE_END( CUL )