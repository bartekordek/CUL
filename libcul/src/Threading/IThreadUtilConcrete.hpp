#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/Threading/IThreadUtil.hpp"

NAMESPACE_BEGIN( CUL )

class ThreadUtilConcrete final: public IThreadUtil
{
public:
    ThreadUtilConcrete();
    ~ThreadUtilConcrete();

protected:
private:
    void setCurrentThreadName( const String& name ) override;
    std::optional<String> getCurrentThreadName() const override;
    std::vector<String> getThreadNames() const override;

    std::map<std::thread::id, String> m_threads;

    ThreadUtilConcrete& operator=( const ThreadUtilConcrete& rhv ) = delete;
    ThreadUtilConcrete& operator=( ThreadUtilConcrete&& rhv ) = delete;
    ThreadUtilConcrete( const ThreadUtilConcrete& arg ) = delete;
    ThreadUtilConcrete( ThreadUtilConcrete&& arg ) = delete;
};

NAMESPACE_END( CUL )