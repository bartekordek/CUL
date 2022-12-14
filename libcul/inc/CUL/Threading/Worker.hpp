#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_queue.hpp"
#include "CUL/STL_IMPORTS/STD_atomic.hpp"

NAMESPACE_BEGIN( CUL )

NAMESPACE_BEGIN( LOG )
class ILogger;
NAMESPACE_END( LOG )

class CULLib_API Worker final
{
public:
	Worker( LOG::ILogger* logger );

	void run();
	void addTask( const std::function<void(void)>& task );
	size_t tasksLeft() const;

	std::atomic<size_t> SleepMS = 1;

	~Worker();
protected:
private:

	void consumeThreadFunction();

	std::atomic_bool m_run = true;
	std::queue< std::function<void( void )>> m_tasks;
	mutable std::mutex m_tasksMtx;

	std::thread m_consumeThread;

	LOG::ILogger* m_logger = nullptr;

private:
	Worker( const Worker& arg ) = delete;
	Worker( Worker&& arg ) = delete;
	Worker& operator=( const Worker& wrkr ) = delete;
	Worker& operator=( Worker&& wrkr ) = delete;
};


NAMESPACE_END( CUL )