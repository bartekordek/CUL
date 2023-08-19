#pragma once

#include "CUL/GenericUtils/Singleton.hpp"
#include "CUL/String.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_deque.hpp"

NAMESPACE_BEGIN( CUL )

class ITask;

class CULLib_API MultiWorkerSystem final: Singleton<MultiWorkerSystem>
{
public:
    MultiWorkerSystem();
    void setWorkersCount( size_t count );
    void startTask( ITask* task );

    void stopWorkers();
    int8_t getCurrentWorkersCount() const;

    uint8_t WorkerSleepBetweenTasksTime = 2u;

    MultiWorkerSystem( const MultiWorkerSystem& ) = delete;
    MultiWorkerSystem( MultiWorkerSystem&& ) = delete;
    MultiWorkerSystem& operator=( const MultiWorkerSystem& ) = delete;
    MultiWorkerSystem& operator=( MultiWorkerSystem&& ) = delete;

    ~MultiWorkerSystem();

protected:
private:
    void addWorker();
    void removeWorker();
    void workerMethod();

    std::vector<std::thread> m_threads;
    mutable std::mutex m_threadsMtx;

    bool m_runWorkers = true;

    std::deque<ITask*> m_tasks;
    std::mutex m_tasksMtx;
};

NAMESPACE_END(CUL)