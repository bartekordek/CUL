#pragma once

#include "CUL/String/String.hpp"

#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_deque.hpp"
#include "CUL/STL_IMPORTS/STD_atomic.hpp"

NAMESPACE_BEGIN( CUL )

NAMESPACE_BEGIN( LOG )
class ILogger;
NAMESPACE_END( LOG )

class CULLib_API Worker final
{
public:
	Worker();
	Worker( LOG::ILogger* logger );

	void run();
	void addTask( const std::function<void(void)>& task );
	size_t tasksLeft() const;
	void setRemoveTasksWhenConsumed( bool enable );

	std::atomic<size_t> SleepMS = 1;

	void setThreadName( const String& name );

	~Worker();
protected:
private:

	void consumeThreadFunction();
	std::atomic_bool m_removeTasksWhenConsumed = true;
	std::atomic_bool m_run = true;
	std::deque< std::function<void( void )>> m_tasks;
	mutable std::mutex m_tasksMtx;

	std::thread m_consumeThread;

	LOG::ILogger* m_logger = nullptr;

	bool m_updateThreadName = false;
	String m_threadName;

private:
	Worker( const Worker& arg ) = delete;
	Worker( Worker&& arg ) = delete;
	Worker& operator=( const Worker& wrkr ) = delete;
	Worker& operator=( Worker&& wrkr ) = delete;
};


NAMESPACE_END( CUL )