#pragma once

#include "CUL/CUL.hpp"

#include "CUL/GenericUtils/ScopeExit.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_bitset.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_thread.hpp"
#include "CUL/STL_IMPORTS/STD_mutex.hpp"
#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_memory_resource.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable : 5045 )
#endif

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

template <size_t PoolSize>
class MemoryPool final
{
public:
    CULLib_API MemoryPool() : m_buffer_src( &m_bufferBlocks, sizeof( m_bufferBlocks ) ), m_allocatedBlocks( &m_buffer_src )
    {
        init();
    }

    CULLib_API void* getMemory( size_t sizeInBytes )
    {
        GUTILS::ScopeExit onExit(
            [this]()
            {
                m_access.unlock();
            } );

        while( !m_access.try_lock() )
        {
        }

        if( m_allocatedBlocks.empty() )
        {
            if( g_buffer.size() >= sizeInBytes )
            {
                BlockInfo bi;
                bi.start = 0;
                bi.end = sizeInBytes - 1;
                bi.ptr = (void*)&g_buffer[0];
                addBlock( &bi );
                return bi.ptr;
            }
        }
        else
        {
            const size_t blocksSize = m_allocatedBlocks.size();
            BlockInfo* lastBlock = nullptr;
            if( blocksSize == 1 )
            {
                lastBlock = &m_allocatedBlocks[0];
            }
            else
            {
                for( size_t i = 1; i < blocksSize; ++i )
                {
                    const BlockInfo& brockPrev = m_allocatedBlocks[i - 1];
                    const BlockInfo& block = m_allocatedBlocks[i];
                    const auto diff = block.start - brockPrev.end - 1;
                    if( diff != 0 )
                    {
                        // Found in the between.
                        if( diff >= sizeInBytes )
                        {
                            BlockInfo bi;
                            bi.start = brockPrev.end + 1;
                            bi.end = brockPrev.end + sizeInBytes;
                            bi.ptr = (void*)( &g_buffer[bi.start] );
                            addBlock( &bi );

                            return bi.ptr;
                        }
                    }
                    lastBlock = &m_allocatedBlocks[i];
                }
            }

            if( lastBlock )
            {
                const size_t leftSpace = ( g_buffer.size() - lastBlock->end ) - 1;
                if( leftSpace > sizeInBytes )
                {
                    BlockInfo bi;
                    bi.start = lastBlock->end + 1;
                    bi.end = lastBlock->end + sizeInBytes;
                    bi.ptr = (void*)( &g_buffer[bi.start] );
                    addBlock( &bi );
                    return bi.ptr;
                }
            }
        }

        return nullptr;
    }
    CULLib_API bool release( void* target )
    {
        if( !m_initialized )
        {
            return false;
        }

        GUTILS::ScopeExit onExit(
            [this]()
            {
                m_access.unlock();
            } );

        while( !m_access.try_lock() )
        {
        }

        auto it = std::find_if( m_allocatedBlocks.begin(), m_allocatedBlocks.end(),
                                [target]( const BlockInfo& bi )
                                {
                                    return bi.ptr == target;
                                } );
        if( it == m_allocatedBlocks.end() )
        {
            for( int i = 0; i < 10; ++i )
            {
            }
        }
        else
        {
            BlockInfo& targetI = *it;
            for( size_t i = targetI.start; i <= targetI.end; ++i )
            {
                g_buffer[i] = std::byte{ 0 };
            }

            m_allocatedBlocks.erase( it );
            return true;
        }
        return false;
    }

    CULLib_API bool release( void* target, const size_t size )
    {
        size_t howManyTimes = size / 8;
        void* startAdd = target;
        for( size_t i = 0; i < howManyTimes; ++i )
        {
            if( !release( startAdd ) )
            {
                return false;
            }
            startAdd = static_cast<char*>( startAdd ) + 1;
        }

        return true;
    }

    CULLib_API size_t getBufferSize() const
    {
        return g_buffer.size();
    }

    CULLib_API bool isInitialized() const
    {
        return m_initialized;
    }
    CULLib_API bool exist( void* target ) const
    {
        auto it = std::find_if( m_allocatedBlocks.begin(), m_allocatedBlocks.end(),
                                [target]( const BlockInfo& bi )
                                {
                                    return bi.ptr == target;
                                } );
        return it != m_allocatedBlocks.end();
    }

    CULLib_API ~MemoryPool()
    {
    }

protected:
private:
    void addBlock( BlockInfo* block )
    {
        m_allocatedBlocks.push_back( *block );
        std::sort( m_allocatedBlocks.begin(), m_allocatedBlocks.end(),
                   []( const BlockInfo& b1, const BlockInfo& b2 )
                   {
                       return b1.start < b2.start;
                   } );
    }
    void init()
    {
        if( !m_initialized )
        {
            std::memset( g_buffer.data(), 0, sizeof( *g_buffer.begin() ) * g_buffer.size() );
            m_initialized = true;
        }
    }
    std::mutex m_access;
    bool m_initialized = false;

    std::array<std::byte, PoolSize> m_bufferBlocks;
    std::pmr::monotonic_buffer_resource m_buffer_src;
    std::pmr::vector<BlockInfo> m_allocatedBlocks;

    std::array<std::byte, PoolSize> g_buffer;

    size_t m_heapAllocCounter = 0;

    MemoryPool( const MemoryPool& arg ) = delete;
    MemoryPool( MemoryPool&& arg ) = delete;
    MemoryPool& operator=( const MemoryPool& rhv ) = delete;
    MemoryPool& operator=( MemoryPool&& rhv ) = delete;
};

NAMESPACE_END( Memory )
NAMESPACE_END( CUL )

#ifdef _MSC_VER
#pragma warning( pop )
#endif