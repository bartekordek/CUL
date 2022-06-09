#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_bitset.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Memory )

class MemoryPool final
{
public:
    CULLib_API MemoryPool();

    CULLib_API void* getMemory( size_t sizeInBytes );
    CULLib_API void release( void* target );
    CULLib_API size_t getBufferSize() const;

    CULLib_API  ~MemoryPool();

protected:
private:
    struct BlockInfo
    {
        size_t start = 0;
        size_t end = 0;
        void* ptr = nullptr;
    };

    void addBlock(BlockInfo* block);

    std::array<std::byte, 2048> m_buffer;

    std::vector<BlockInfo> m_allocatedBlocks;


    MemoryPool(const MemoryPool& arg) = delete;
    MemoryPool(MemoryPool&& arg) = delete;
    MemoryPool& operator=(const MemoryPool& rhv) = delete;
    MemoryPool& operator=(MemoryPool&& rhv) = delete;
};

NAMESPACE_END( Memory )
NAMESPACE_END( CUL )