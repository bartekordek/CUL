#pragma once

#include <CUL/String/StringWrapper.hpp>
#include <CUL/GenericUtils/NonCopyable.hpp>
#include <CUL/STL_IMPORTS/STD_functional.hpp>
#include <CUL/STL_IMPORTS/STD_memory.hpp>

namespace CUL
{
class CDiskScheduler_impl;

class CDiskScheduler
{
public:
    CULLib_API static CDiskScheduler& getInstance();
    CULLib_API void executeWhenPossibleWithWait( const StringWr& inPath,
                                                  std::function<void( void )> inFunction );

    // Busy-% above this value delays big-file MD5 (with a short timeout).
    CULLib_API static float getSafeThresholdPercent();

    CUL_NONCOPYABLE( CDiskScheduler );

protected:
private:
    CDiskScheduler();
    ~CDiskScheduler();

    std::unique_ptr<CDiskScheduler_impl> m_impl;
};
}  // namespace CUL