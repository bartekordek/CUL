#pragma once

#include "CUL/GenericUtils/Singleton.hpp"
#include "CUL/String.hpp"
#include "CUL/Threading/Priority.hpp"
#include "CUL/Threading/ThreadUtilObserver.hpp"

#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_deque.hpp"
#include "CUL/STL_IMPORTS/STD_unordered_map.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_future.hpp"

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

class CULLib_API MultiWorkerSystem final: public Singleton<MultiWorkerSystem>, public CThreadUtilObserver
{
public:
    MultiWorkerSystem();
    void registerTask( ITask* task );

    void addWorker( EPriority priority );
    void removeWorker( EPriority priority );
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
    void workerMethod( int8_t threadId, EPriority priority );
    void onThreadsStateUpdated( const std::vector<ThreadMeta>& ti ) override;
    void removeThreadFromWorkers( const std::thread::id& id );

    std::unordered_map<std::thread::id, ThreadInfo*> m_threads;
    mutable std::mutex m_threadsMtx;

    bool m_runWorkers = true;
    std::unordered_map<int8_t, bool> m_workersRun;
    std::mutex m_workersRunMtx;

    mutable std::array<std::deque<ITask*>, (size_t)EPriority::COUNT> m_tasksArray;
    mutable std::array<std::mutex, (size_t)EPriority::COUNT> m_tasksMtxs;

    std::unordered_map<EPriority, int> m_sleepMapping;


    //void updateWorkerStatus( const std::vector<String>& in );
    //void fetchWorkerStatus();
    //std::vector<String> m_workerStatus;
    //std::mutex m_workerStatusMtx;

    std::future<void> m_changeWorkers;
};

NAMESPACE_END(CUL)