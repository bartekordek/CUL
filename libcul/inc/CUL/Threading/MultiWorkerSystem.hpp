#pragma once

#include "CUL/GenericUtils/Singleton.hpp"
#include "CUL/String.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_deque.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"

NAMESPACE_BEGIN( CUL )

class ITask;

class CULLib_API MultiWorkerSystem final: public Singleton<MultiWorkerSystem>
{
public:
    MultiWorkerSystem();
    void setWorkersCount( size_t count );
    void startTask( ITask* task );

    void stopWorkers();
    int8_t getCurrentWorkersCount() const;
    uint8_t getTasksLeft() const;

    uint8_t WorkerSleepBetweenTasksTimeMs = 0u;
    uint8_t WorkerSleepWhenNoTaskTimeMs = 0u;
    void setWorkerThreadName( int8_t id, const String& name );

    int8_t getCurrentThreadWorkerId() const;

    std::vector<String> getWorkersStatuses();

    MultiWorkerSystem( const MultiWorkerSystem& ) = delete;
    MultiWorkerSystem( MultiWorkerSystem&& ) = delete;
    MultiWorkerSystem& operator=( const MultiWorkerSystem& ) = delete;
    MultiWorkerSystem& operator=( MultiWorkerSystem&& ) = delete;

    ~MultiWorkerSystem();

protected:
private:
    void addWorker();
    void removeWorker();
    void workerMethod( int8_t threadId );

    std::vector<std::thread> m_threads;
    mutable std::mutex m_threadsMtx;

    bool m_runWorkers = true;
    std::map<int8_t, bool> m_workersRun;
    std::mutex m_workersRunMtx;

    std::deque<ITask*> m_tasks;
    mutable std::mutex m_tasksMtx;

    std::map<std::thread::id, int8_t> m_threadToWorkerIdMapping;
    mutable std::mutex m_threadToWorkerIdMappingMtx;
};

NAMESPACE_END(CUL)