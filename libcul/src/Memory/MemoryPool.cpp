#include "CUL/Memory/MemoryPool.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/GenericUtils/ScopeExit.hpp"

#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/STL_IMPORTS/STD_cassert.hpp"

#define assertm(exp, msg) assert(((void)msg, exp))

using namespace CUL;
using namespace Memory;


//bool MemoryPool::s_initialized = false;
CUL::LOG::ILogger* MemoryPool::s_logger = nullptr;

MemoryPool& MemoryPool::getInstance()
{
    static MemoryPool g_instance;
    return g_instance;
}

MemoryPool::MemoryPool() : m_buffer_src( &m_bufferBlocks, sizeof( m_bufferBlocks ) ), m_allocatedBlocks( &m_buffer_src )
{
    init();
}

void MemoryPool::init()
{
    std::lock_guard<std::mutex> mtxGuard( m_access );
    if( !m_initialized )
    {
        std::memset( g_buffer.data(), 0, sizeof( *g_buffer.begin() ) * g_buffer.size() );
        std::cout << "Stack begin: " << g_buffer.data() << "\n";
        m_initialized = true;
    }
}

void* MemoryPool::getMemory( size_t sizeInBytes )
{
    GUTILS::ScopeExit onExit( [this]() {
        m_access.unlock();
    } );

    while( !m_access.try_lock() )
    {
    }

    if( m_allocatedBlocks.empty() )
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

    //std::cerr << "Stack pool is full, creating on heap [" << ++m_heapAllocCounter  << "].\n";
    return nullptr;
}

void MemoryPool::addBlock( BlockInfo* block )
{
    m_allocatedBlocks.push_back( *block );
    std::sort( m_allocatedBlocks.begin(), m_allocatedBlocks.end(),
               []( const BlockInfo& b1, const BlockInfo& b2 )
               {
                   return b1.start < b2.start;
    } );
}

bool MemoryPool::isInitialized() const
{
    return m_initialized;
}

bool MemoryPool::exist( void* target ) const
{
    auto it = std::find_if( m_allocatedBlocks.begin(), m_allocatedBlocks.end(), [target]( const BlockInfo& bi ) {
        return bi.ptr == target;
    } );
    return it != m_allocatedBlocks.end();
}

bool MemoryPool::release( void* target, const size_t size )
{
    size_t howManyTimes = size / 8;
    void* startAdd = target;
    for( size_t i = 0; i < howManyTimes; ++i )
    {
        if( !release( startAdd ) )
        {
            return false;
        }
        startAdd = static_cast<char*>(startAdd) + 1;
    }

    return true;
}

bool MemoryPool::release( void* target )
{
    if( !m_initialized )
    {
        return false;
    }

    GUTILS::ScopeExit onExit( [this]() {
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

size_t MemoryPool::getBufferSize() const
{
    return g_buffer.size();
}

MemoryPool::~MemoryPool()
{

}