#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_bitset.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_memory_resource.hpp"

NAMESPACE_BEGIN( CUL )

NAMESPACE_BEGIN( LOG )
class ILogger;
NAMESPACE_END( LOG )

NAMESPACE_BEGIN( Memory )

struct CULLib_API BlockInfo
{
    size_t start = 0;
    size_t end = 0;
    void* ptr = nullptr;
};

// constexpr size_t G_arraySize = 8192;
//constexpr size_t G_arraySize = 16384;
constexpr size_t G_arraySize = 32768;

class MemoryPool final
{
public:
    CULLib_API static MemoryPool& getInstance();

    CULLib_API void* getMemory( size_t sizeInBytes );
    CULLib_API bool release( void* target );
    CULLib_API bool release( void* target, const size_t size );
    CULLib_API size_t getBufferSize() const;

    CULLib_API bool isInitialized() const;
    CULLib_API bool exist( void* target ) const;

    static LOG::ILogger* s_logger;

protected:
private:
    void addBlock(BlockInfo* block);
    void init();
    std::mutex m_access;
    bool m_initialized = false;

    std::array<std::byte, G_arraySize> m_bufferBlocks;
    std::pmr::monotonic_buffer_resource m_buffer_src;
    std::pmr::vector<BlockInfo> m_allocatedBlocks;

    std::array<std::byte, G_arraySize> g_buffer;

    size_t m_heapAllocCounter = 0;

    CULLib_API MemoryPool();
    CULLib_API ~MemoryPool();

    MemoryPool(const MemoryPool& arg) = delete;
    MemoryPool(MemoryPool&& arg) = delete;
    MemoryPool& operator=(const MemoryPool& rhv) = delete;
    MemoryPool& operator=(MemoryPool&& rhv) = delete;
};

NAMESPACE_END( Memory )
NAMESPACE_END( CUL )