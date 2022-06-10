#include "CUL/Memory/MemoryPool.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

#include "CUL/STL_IMPORTS/STD_algorithm.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

using namespace CUL;
using namespace Memory;

MemoryPool::MemoryPool()
{
    std::memset( m_buffer.data(), 0, sizeof( *m_buffer.begin() ) * m_buffer.size() );
}

void* MemoryPool::getMemory( size_t sizeInBytes )
{
    if( m_allocatedBlocks.empty() )
    {
        if( m_buffer.size() > sizeInBytes )
        {
            BlockInfo bi;
            bi.start = 0;
            bi.end = sizeInBytes - 1;
            bi.ptr = (void*)&m_buffer[0];
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
                        bi.ptr = (void*)( &m_buffer[bi.start] );
                        addBlock( &bi );
                        return bi.ptr;
                    }
                }
                lastBlock = &m_allocatedBlocks[i];
            }
        }

        const size_t leftSpace = (m_buffer.size() - lastBlock->end) - 1;
        if( lastBlock && leftSpace > sizeInBytes )
        {
            BlockInfo bi;
            bi.start = lastBlock->end + 1;
            bi.end = lastBlock->end + sizeInBytes;
            bi.ptr = (void*)( &m_buffer[bi.start] );
            addBlock( &bi );
            return bi.ptr;
        }
    }

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

void MemoryPool::release( void* target )
{
    auto it = std::find_if( m_allocatedBlocks.begin(), m_allocatedBlocks.end(),
                         [target]( const BlockInfo& bi )
                         {
                             return bi.ptr == target;
                         } );
    if( it == m_allocatedBlocks.end() )
    {
        Assert::simple( false, "Cannot find element on memory pool!" );
    }
    else
    {
        BlockInfo& targetI = *it;
        for( size_t i = targetI.start; i <= targetI.end; ++i )
        {
            m_buffer[i] = std::byte{0};
        }

        m_allocatedBlocks.erase( it );
    }
}

size_t MemoryPool::getBufferSize() const
{
    return m_buffer.size();
}

MemoryPool::~MemoryPool()
{
}