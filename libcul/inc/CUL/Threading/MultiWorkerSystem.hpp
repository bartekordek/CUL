#pragma once

#include "CUL/GenericUtils/Singleton.hpp"
#include "CUL/String.hpp"
#include "CUL/Threading/Priority.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_deque.hpp"
#include "CUL/STL_IMPORTS/STD_unordered_map.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"

NAMESPACE_BEGIN( CUL )

class ITask;

struct ThreadInfo final
{
    ThreadInfo() = default;
    ThreadInfo( const ThreadInfo& ) = delete;
    ThreadInfo( ThreadInfo&& ) noexcept ;

    ThreadInfo& operator=( const ThreadInfo& ti ) = delete;
    ThreadInfo& operator=( ThreadInfo&& ti ) noexcept;

    ~ThreadInfo() = default;

    std::thread Thread;
    int8_t WorkerId = -1;
    EPriority Priority = EPriority::None;
};

class CULLib_API MultiWorkerSystem final: public Singleton<MultiWorkerSystem>
{
public:
    MultiWorkerSystem();
    void registerTask( ITask* task );

    void addWorker( EPriority priority );
    void stopWorkers();
    int8_t getCurrentWorkersCount() const;
    uint8_t getTasksLeft( EPriority priority ) const;

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
    
    void removeWorker( EPriority priority );
    void workerMethod( int8_t threadId, EPriority priority );

    std::vector<ThreadInfo> m_threads;
    mutable std::mutex m_threadsMtx;

    bool m_runWorkers = true;
    std::unordered_map<int8_t, bool> m_workersRun;
    std::mutex m_workersRunMtx;

    mutable std::array<std::deque<ITask*>, (size_t)EPriority::COUNT> m_tasksArray;
    mutable std::array<std::mutex, (size_t)EPriority::COUNT> m_tasksMtxs;

    std::unordered_map<EPriority, int> m_sleepMapping;
};

NAMESPACE_END(CUL)