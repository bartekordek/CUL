#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

namespace CUL
{
class CTaskAccumulator final
{
public:
    CULLib_API CTaskAccumulator();

    CULLib_API void addTask( std::function<void( void )> inTask );
    CULLib_API void executeOne();
    CULLib_API void executeAll();

    CULLib_API ~CTaskAccumulator();

    CTaskAccumulator( const CTaskAccumulator& ) = delete;
    CTaskAccumulator( CTaskAccumulator&& ) = delete;
    CTaskAccumulator& operator=( const CTaskAccumulator& ) = delete;
    CTaskAccumulator& operator=( CTaskAccumulator&& ) = delete;

protected:
private:
    std::vector<std::function<void( void )>> m_tasks;
    std::mutex m_tasksMtx;
};
}  // namespace CUL