#if defined( CUL_STATIC )

#include "CUL/Memory/MemoryTracker.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/GenericUtils/ScopeExit.hpp"
#include "CUL/STL_IMPORTS/STD_deque.hpp"
#include "IMPORT_boost_stacktrace.hpp"

NAMESPACE_BEGIN( CUL )

thread_local bool g_blockCurrentThread = false;

struct StackInfo final
{
    bool Register{ true };
    std::unique_ptr<boost::stacktrace::stacktrace> Trace;
    std::size_t Size{ 0u };
    void* Data{ nullptr };
    std::size_t SkipFirstLinesCount{ 0u };

    StackInfo() = default;

    StackInfo( bool inRegister, std::size_t inSize, void* inPtr, std::size_t inSkipFirstLinesCount )
        : Register( inRegister ),
          Trace( std::make_unique<boost::stacktrace::stacktrace>() ),
          Size( inSize ),
          Data( inPtr ),
          SkipFirstLinesCount( inSkipFirstLinesCount )
    {
    }

    StackInfo( const StackInfo& rhv ) = delete;
    StackInfo( StackInfo&& arg ) noexcept:
        Register( arg.Register ),
        Trace( std::move( arg.Trace ) ),
          Size( arg.Size ),
          Data( arg.Data ),
          SkipFirstLinesCount( arg.SkipFirstLinesCount )
    {
        arg.Size = 0u;
        arg.Data = nullptr;
        arg.SkipFirstLinesCount = 0u;
    }


    StackInfo& operator=( const StackInfo& arg ) = delete;
    StackInfo& operator=(StackInfo&& arg) noexcept
    {
        if( this  != &arg )
        {
            Register = arg.Register;
            Trace = std::move( arg.Trace );
            Size = arg.Size;
            Data = arg.Data;
            SkipFirstLinesCount = arg.SkipFirstLinesCount;

            arg.Size = 0u;
            arg.Data = nullptr;
        }
        return *this;
    }

    ~StackInfo() = default;
};

namespace Deque
{
    static constexpr std::uint64_t PoolSize = 8u * 1024u * 1024u;  // 16MB
    std::array<std::byte, PoolSize> BufferBlocks;
    std::pmr::monotonic_buffer_resource BufferSrc{ BufferBlocks.data(), PoolSize };

    std::pmr::deque<StackInfo> g_traceDeque{ &BufferSrc };
}

MemoryTracker& MemoryTracker::getInstance()
{
    static MemoryTracker instance;
    return instance;
}

MemoryTracker::MemoryTracker()
{
}

void MemoryTracker::init()
{
    if( m_initialized )
    {
        return;
    }
    m_mainLoopThread = std::thread( &MemoryTracker::mainLoop, this );
    m_initialized = true;
}

void MemoryTracker::logRealloc( void* inOldPtr, void* inNewPtr, std::uint64_t inSize, std::size_t skipFirstLinesCount )
{
    if( ( g_blockCurrentThread == true ) || ( m_enableTracking == false ) )
    {
        return;
    }
    logFree( inOldPtr );
    logAlloc( inNewPtr, inSize, skipFirstLinesCount );
}

void MemoryTracker::logAlloc( void* inPtr, std::uint64_t inSize, std::size_t skipFirstLinesCount )
{
    if( ( g_blockCurrentThread == true ) || ( m_enableTracking == false ) )
    {
        return;
    }

    registerStack( inPtr, inSize, skipFirstLinesCount );
}

void MemoryTracker::logFree( void* inPtr )
{
    if( ( g_blockCurrentThread == true ) || ( m_enableTracking == false ) )
    {
        return;
    }

    unregisterStack( inPtr, 0u, 0u );
}

void MemoryTracker::toggleTracking( bool inToggleTracking )
{
    m_enableTracking = inToggleTracking;
}

void MemoryTracker::registerStack( void* ptr, std::uint64_t inSize, std::size_t skipFirstLinesCount )
{
    StackInfo si;
    si.Data = ptr;
    si.Register = true;
    si.Size = inSize;
    si.SkipFirstLinesCount = skipFirstLinesCount;
    g_blockCurrentThread = true;
    si.Trace = std::make_unique<boost::stacktrace::stacktrace>();
    g_blockCurrentThread = false;

    std::lock_guard<std::mutex> locker( g_traceDequeMtx );
    Deque::g_traceDeque.emplace_back( std::move( si ) );
}

void MemoryTracker::unregisterStack( void* ptr, std::uint64_t inSize, std::size_t skipFirstLinesCount )
{
    StackInfo si;
    si.Data = ptr;
    si.Register = false;
    si.Size = inSize;
    si.SkipFirstLinesCount = skipFirstLinesCount;

    std::lock_guard<std::mutex> locker( g_traceDequeMtx );
    Deque::g_traceDeque.emplace_back( std::move( si ) );
}

void MemoryTracker::mainLoop()
{
    StackInfo currentTrace;
    bool found{ false };
    while( m_runMainLoop )
    {
        {
            std::lock_guard<std::mutex> locker( g_traceDequeMtx );
            if( Deque::g_traceDeque.empty() == false )
            {
                g_blockCurrentThread = true;
                currentTrace = std::move( Deque::g_traceDeque.back() );
                Deque::g_traceDeque.pop_back();
                g_blockCurrentThread = false;
                found = true;
            }
            else
            {
                found = false;
            }
        }
        if( found )
        {
            decode( currentTrace );
            found = false;
        }
    }
}

void convertBoostToAllocationInfo( AllocationInfo& out, const boost::stacktrace::stacktrace& stackTrace )
{
    StackLinesArray& outStackLines = out.StackLines;

    const auto& stVec = stackTrace.as_vector();
    size_t stackTraceSize = stVec.size();
    std::size_t outputStackSize{ 0u };
    for( size_t i = 0; i < stackTraceSize; ++i )
    {
        const boost::stacktrace::frame& currentTraceLine = stVec[i];
        if( currentTraceLine.empty() == true )
        {
            continue;
        }

        if( outputStackSize >= G_maxStackSize )
        {
            return;
        }

        char buff[1024];
        std::string sourceFile = currentTraceLine.source_file();
        if( sourceFile.empty() )
        {
            sourceFile = "unkown";
        }

        if( ( sourceFile.find( "MemoryTracker" ) != std::string::npos ) || ( sourceFile.find( "stacktrace.hpp" ) != std::string::npos ) ||
            ( sourceFile.find( "MemoryUtils." ) != std::string::npos ) )
        {
            continue;
        }

        sprintf( buff, "%s:%d", sourceFile.c_str(), (int)currentTraceLine.source_line() );

        outStackLines[outputStackSize] = buff;
        ++outputStackSize;
        if( outputStackSize == out.Size )
        {
            break;
        }
    }
}

void MemoryTracker::decode( const StackInfo& stackInfo )
{
    if( stackInfo.Register )
    {
        AllocationInfo ai;
        convertBoostToAllocationInfo(ai, *stackInfo.Trace);
        ai.Size = stackInfo.Size;
        std::lock_guard<std::mutex> locker( m_dataMtx );
        g_blockCurrentThread = true;
        m_allocations[stackInfo.Data] = ai;
        g_blockCurrentThread = false;
    }
    else
    {
        std::lock_guard<std::mutex> locker( m_dataMtx );
        const auto it = m_allocations.find( stackInfo.Data );
        if( it != m_allocations.end() )
        {
            m_allocations.erase( it );
        }
    }
}

void MemoryTracker::getStackHere( StackLinesArray& outStackLines, std::size_t skipFirstLinesCount )
{
    g_blockCurrentThread = true;
    GUTILS::ScopeExit se([](){
            g_blockCurrentThread = false;
    } );

    boost::stacktrace::stacktrace stackTrace;
    boost::stacktrace::frame copy;
    const auto& stVec = stackTrace.as_vector();
    size_t stackTraceSize = stVec.size();
    std::size_t outputStackSize{ 0u };
    for( size_t i = 0; i < stackTraceSize; ++i )
    {
        const boost::stacktrace::frame& currentTraceLine = stVec[i];
        if (currentTraceLine.empty() == true)
        {
            continue;
        }

        if( outputStackSize >= G_maxStackSize )
        {
            return;
        }

        if( i < skipFirstLinesCount )
        {
            continue;
        }

        char buff[1024];
        std::string sourceFile = currentTraceLine.source_file();
        if( sourceFile.empty() )
        {
            sourceFile = "unkown";
        }

        sprintf( buff, "%s:%d", sourceFile.c_str(), (int)currentTraceLine.source_line() );

        outStackLines[outputStackSize] = buff;
        ++outputStackSize;
    }
}

void MemoryTracker::dumpActiveAllocations() const
{
    LOG::ILogger& logger = LOG::ILogger::getInstance();

    std::lock_guard<std::mutex> locker( m_dataMtx );
    for( const auto& [addr, stackInfo]: m_allocations )
    {
        logger.logVariable(LOG::Severity::INFO, "Stack info:\nsize:%d bytes\n", stackInfo.Size );

        for( const auto& line: stackInfo.StackLines )
        {
            logger.log( line.c_str() );
        }
    }
}

bool MemoryTracker::waitForAllCallStacksToBeDecoded() const
{
    bool dequeIsEmpty{ false };
    while( dequeIsEmpty == false )
    {
        std::lock_guard<std::mutex> locker( g_traceDequeMtx );
        dequeIsEmpty = Deque::g_traceDeque.empty();
    }

    return true;
}

CULLib_API std::int32_t MemoryTracker::getActiveAllocations() const
{
    std::lock_guard<std::mutex> locker( m_dataMtx );
    return m_allocations.size();
}

MemoryTracker::~MemoryTracker()
{
    m_runMainLoop = false;
    if( m_mainLoopThread.joinable() )
    {
        m_mainLoopThread.join();
    }
}

NAMESPACE_END( CUL )

#endif  // #if defined( CUL_STATIC )