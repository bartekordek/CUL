#include "CUL/Memory/MemoryUtils.hpp"
#include "CUL/Memory/MemoryTracker.hpp"
#include "CUL/STL_IMPORTS/STD_cstdint.hpp"

NAMESPACE_BEGIN( CUL )

#if defined( CUL_STATIC )
void TrackRealloc( void* oldPtr, void* newPtr, std::uint64_t inSize )
{
    MemoryTracker::getInstance().logRealloc( oldPtr, newPtr, inSize, 5u );
}

void TrackAlloc( void* inAddr, std::uint64_t inSize )
{
    MemoryTracker::getInstance().logAlloc( inAddr, inSize, 5u );
}

void TrackFree( void* inAddr )
{
    MemoryTracker::getInstance().logFree( inAddr );
}
#endif  // #if defined( CUL_STATIC )

NAMESPACE_END( CUL )

#if CUL_GLOBAL_MEMORY_POOL

void* operator new( std::size_t size )
{
    void* result = nullptr;
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() )
    {
        result = Singleton<Memory::MemoryPool>::getInstance().getMemory( size );
        if( result )
        {
            CUL::TrackAlloc( result );
            return result;
        }
        else
        {
            result = std::malloc( size );
            CUL::TrackAlloc( result );
            return result;
        }
    }
    else
    {
        result = std::malloc( size );
        CUL::TrackAlloc( result );
        return result;
    }
}

void* operator new[]( std::size_t size )
{
    void* result = nullptr;
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() )
    {
        result = Singleton<Memory::MemoryPool>::getInstance().getMemory( size );
        if( result )
        {
            CUL::TrackAlloc( result );
            return result;
        }
        else
        {
            result = std::malloc( size );
            CUL::TrackAlloc( result );
            return result;
        }
    }
    else
    {
        result = std::malloc( size );
        CUL::TrackAlloc( result );
        return result;
    }
}

void operator delete( void* p ) throw()
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() && Singleton<Memory::MemoryPool>::getInstance().exist( p ) )
    {
        CUL::TrackFree( p );
        Singleton<Memory::MemoryPool>::getInstance().release( p );
    }
    else
    {
        CUL::TrackFree( p );
        std::free( p );
    }
}

void operator delete( void* p, std::size_t targetSize ) throw()
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() && Singleton<Memory::MemoryPool>::getInstance().exist( p ) )
    {
        CUL::TrackFree( p );
        Singleton<Memory::MemoryPool>::getInstance().release( p, targetSize );
    }
    else
    {
        CUL::TrackFree( p );
        std::free( p );
    }
}

void operator delete[]( void* p ) throw()
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() && Singleton<Memory::MemoryPool>::getInstance().exist( p ) )
    {
        CUL::TrackFree( p );
        Singleton<Memory::MemoryPool>::getInstance().release( p );
    }
    else
    {
        TrackFree( p );
        std::free( p );
    }
}

void operator delete[]( void* p, std::size_t /* targetSize */ ) throw()
{
    if( Singleton<Memory::MemoryPool>::getInstance().isInitialized() && Singleton<Memory::MemoryPool>::getInstance().exist( p ) )
    {
        CUL::TrackFree( p );
        Singleton<Memory::MemoryPool>::getInstance().release( p );
    }
    else
    {
        CUL::TrackFree( p );
        std::free( p );
    }
}
#elif defined( TRACY_ENABLE ) && defined( CUL_STATIC ) && defined( TRACY_CALLSTACK )
    #include "CUL/IMPORT_tracy.hpp"
constexpr std::size_t g_callstackDepth = 32u;
void* operator new( std::size_t count )
{
    auto ptr = malloc( count );
    CUL::TrackAlloc( ptr, count );
    TracyAllocS( ptr, count, g_callstackDepth );
    return ptr;
}

void operator delete( void* ptr, std::size_t )
{
    CUL::TrackFree( ptr );
    TracyFreeS( ptr, g_callstackDepth );
    free( ptr );
}

void operator delete( void* ptr ) noexcept
{
    CUL::TrackFree( ptr );
    TracyFreeS( ptr, g_callstackDepth );
    free( ptr );
}
#endif  // #ifdef CUL_GLOBAL_MEMORY_POOL