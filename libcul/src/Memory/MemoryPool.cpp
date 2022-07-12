#include "CUL/Memory/MemoryPool.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/GenericUtils/ScopeExit.hpp"

#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;
using namespace Memory;

static std::array<std::byte, 8192> g_buffer;
static std::array<std::byte, 8192> g_bufferBlocks;

static std::pmr::monotonic_buffer_resource g_buffer_src( &g_bufferBlocks, sizeof( g_bufferBlocks ) );
static std::pmr::vector<BlockInfo> g_allocatedBlocks( &g_buffer_src );

bool MemoryPool::s_initialized = false;
CUL::LOG::ILogger* MemoryPool::s_logger = nullptr;

MemoryPool::MemoryPool()
{
    init();
}

void MemoryPool::init()
{
    std::lock_guard<std::mutex> mtxGuard( m_access );
    if( !s_initialized )
    {
        std::memset( g_buffer.data(), 0, sizeof( *g_buffer.begin() ) * g_buffer.size() );
        s_initialized = true;
    }
}

void* MemoryPool::getMemory( size_t sizeInBytes )
{
    if( !s_initialized )
    {
        return nullptr;
    }

    GUTILS::ScopeExit onExit( [this]() {
        m_access.unlock();
    } );

    while( !m_access.try_lock() )
    {
    }

    if( g_allocatedBlocks.empty() )
    {
        if( g_buffer.size() > sizeInBytes )
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
        const size_t blocksSize = g_allocatedBlocks.size();
        BlockInfo* lastBlock = nullptr;
        if( blocksSize == 1 )
        {
            lastBlock = &g_allocatedBlocks[0];
        }
        else
        {
            for( size_t i = 1; i < blocksSize; ++i )
            {
                const BlockInfo& brockPrev = g_allocatedBlocks[i - 1];
                const BlockInfo& block = g_allocatedBlocks[i];
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
                lastBlock = &g_allocatedBlocks[i];
            }
        }

        const size_t leftSpace = ( g_buffer.size() - lastBlock->end ) - 1;
        if( lastBlock && leftSpace > sizeInBytes )
        {
            BlockInfo bi;
            bi.start = lastBlock->end + 1;
            bi.end = lastBlock->end + sizeInBytes;
            bi.ptr = (void*)( &g_buffer[bi.start] );
            addBlock( &bi );
            return bi.ptr;
        }
    }

    std::cerr << "Stack pool is full, creating on heap.\n";
    return nullptr;
}

void MemoryPool::addBlock( BlockInfo* block )
{
    g_allocatedBlocks.push_back( *block );
    std::sort( g_allocatedBlocks.begin(), g_allocatedBlocks.end(),
               []( const BlockInfo& b1, const BlockInfo& b2 )
               {
                   return b1.start < b2.start;
    } );
}

bool MemoryPool::release( void* target )
{
    if( !s_initialized )
    {
        return false;
    }

    GUTILS::ScopeExit onExit( [this]() {
        m_access.unlock();
    } );

    while( !m_access.try_lock() )
    {
    }

    auto it = std::find_if( g_allocatedBlocks.begin(), g_allocatedBlocks.end(),
                         [target]( const BlockInfo& bi )
                         {
                             return bi.ptr == target;
                         } );
    if( it == g_allocatedBlocks.end() )
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

        g_allocatedBlocks.erase( it );
        return true;
    }
    return false;
}

size_t MemoryPool::getBufferSize() const
{
    return g_buffer.size();
}

MemoryPool::~MemoryPool()
{
}