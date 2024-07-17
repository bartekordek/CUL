#pragma once

#include "CUL/CUL.hpp"
#include "CUL/Threading/ThreadWrap.hpp"
#include "CUL/StringStatic.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"
#include "CUL/STL_IMPORTS/STD_unordered_map.hpp"
#include "CUL/STL_IMPORTS/STD_memory_resource.hpp"

NAMESPACE_BEGIN( CUL )

constexpr std::uint8_t G_maxStackSize = 8u;

using StackString = StringStatic<1024>;
using StackLineString = StringStatic<256>;
using StackLinesArray = std::array<StackLineString, G_maxStackSize>;

struct AllocationInfo
{
    std::uint64_t Size{ 0u };
    StackLinesArray StackLines;
};

class MemoryTracker final
{
public:
    static CULLib_API MemoryTracker& getInstance();
    MemoryTracker( const MemoryTracker& ) = delete;
    MemoryTracker( MemoryTracker&& ) = delete;
    MemoryTracker& operator=( const MemoryTracker& ) = delete;
    MemoryTracker& operator=( MemoryTracker&& ) = delete;

    CULLib_API void logRealloc( void* inOldPtr, std::uint64_t inSize );
    CULLib_API void logAlloc( void* inPtr, std::uint64_t inSize );
    CULLib_API void logFree( void* inPtr );
    CULLib_API void toggleTracking( bool inToggleTracking );
    CULLib_API void dumpActiveAllocations() const;

protected:
private:
    MemoryTracker();
    void getStackHere( StackLinesArray& outStackLines );
    ~MemoryTracker();

    bool m_enableTracking{ false };
    mutable std::mutex m_dataMtx;
    static constexpr std::uint64_t PoolSize = 2u * 1024u;// 2MB
    std::array<std::byte, PoolSize> m_bufferBlocks;
    std::pmr::monotonic_buffer_resource m_buffer_src{ m_bufferBlocks.data(), PoolSize };
    std::pmr::unordered_map<void*, AllocationInfo> m_allocations{ &m_buffer_src };
    //ThreadWrapper m_workerThread;
};

NAMESPACE_END(CUL)