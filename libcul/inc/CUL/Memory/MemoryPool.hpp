#pragma once

#include "CUL/CUL.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_bitset.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_memory_resource.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"

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

class MemoryPool final
{
public:
    CULLib_API MemoryPool();

    CULLib_API void* getMemory( size_t sizeInBytes );
    CULLib_API bool release( void* target );
    CULLib_API size_t getBufferSize() const;


    static LOG::ILogger* s_logger;

    CULLib_API  ~MemoryPool();

protected:
private:
    void addBlock(BlockInfo* block);
    void init();
    std::mutex m_access;
    static bool s_initialized;


    MemoryPool(const MemoryPool& arg) = delete;
    MemoryPool(MemoryPool&& arg) = delete;
    MemoryPool& operator=(const MemoryPool& rhv) = delete;
    MemoryPool& operator=(MemoryPool&& rhv) = delete;
};

NAMESPACE_END( Memory )
NAMESPACE_END( CUL )