#include "CUL/Memory/MemoryTracker.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/GenericUtils/ScopeExit.hpp"
#include "IMPORT_boost_stacktrace.hpp"

NAMESPACE_BEGIN( CUL )

thread_local bool g_blockCurrentThread = false;

MemoryTracker& MemoryTracker::getInstance()
{
    static MemoryTracker instance;
    return instance;
}

MemoryTracker::MemoryTracker()
{
}

void MemoryTracker::logRealloc( void* inOldPtr, std::uint64_t inSize )
{
    if( ( g_blockCurrentThread == true ) || ( m_enableTracking == false ) )
    {
        return;
    }

    AllocationInfo ai;
    ai.Size = inSize;
    getStackHere( ai.StackLines );

    std::lock_guard<std::mutex> locker(m_dataMtx);
    const auto it = m_allocations.find( inOldPtr );
    m_allocations.erase( it );
    m_allocations[inOldPtr] = ai;
}

void MemoryTracker::logAlloc( void* inPtr, std::uint64_t inSize )
{
    if( ( g_blockCurrentThread == true ) || ( m_enableTracking == false ) )
    {
        return;
    }

    AllocationInfo ai;
    ai.Size = inSize;
    getStackHere( ai.StackLines );

    std::lock_guard<std::mutex> locker( m_dataMtx );
    m_allocations[inPtr] = ai;
}

void MemoryTracker::logFree( void* inPtr )
{
    if( ( g_blockCurrentThread == true ) || ( m_enableTracking == false ) )
    {
        return;
    }

    std::lock_guard<std::mutex> locker( m_dataMtx );
    const auto it = m_allocations.find( inPtr );
    m_allocations.erase( it );
}

void MemoryTracker::toggleTracking( bool inToggleTracking )
{
    m_enableTracking = inToggleTracking;
}

void MemoryTracker::getStackHere( StackLinesArray& outStackLines )
{
    g_blockCurrentThread = true;
    GUTILS::ScopeExit se([](){
            g_blockCurrentThread = false;
    } );

    auto stackTrace = boost::stacktrace::stacktrace();
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

        char buff[1024];
        std::string sourceFile = currentTraceLine.source_file();
        if( sourceFile.empty() )
        {
            sourceFile = "unkown";
        }

        if( ( sourceFile.find( "MemoryTracker" ) != std::string::npos) ||
            ( sourceFile.find( "stacktrace.hpp" ) != std::string::npos ) ||
            ( sourceFile.find( "MemoryUtils." ) != std::string::npos ) )
        {
            continue;
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
        logger.logVariable(LOG::Severity::INFO, "Stack info:\nsize:%d bytes\nstack value:", stackInfo.Size );

        for( const auto& line: stackInfo.StackLines )
        {
            logger.log( line.c_str() );
        }
    }
}

MemoryTracker::~MemoryTracker()
{
}

NAMESPACE_END( CUL )