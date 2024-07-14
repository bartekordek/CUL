#include "Memory/MemoryTracker.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/GenericUtils/ScopeExit.hpp"
#include "IMPORT_boost_stacktrace.hpp"

NAMESPACE_BEGIN( CUL )

constexpr std::uint8_t g_maxStackSize = 8u;

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

    StackString ss;
    getStackHere(ss);

    std::lock_guard<std::mutex> locker(m_dataMtx);
    const auto it = m_allocations.find( inOldPtr );
    m_allocations.erase( it );
    m_allocations[inOldPtr] = ss;
}

void MemoryTracker::logAlloc( void* inPtr, std::uint64_t inSize )
{
    if( ( g_blockCurrentThread == true ) || ( m_enableTracking == false ) )
    {
        return;
    }

    StackString ss;
    getStackHere( ss );

    std::lock_guard<std::mutex> locker( m_dataMtx );
    m_allocations[inPtr] = ss;
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

void MemoryTracker::getStackHere( StackString& outString )
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

        if( outputStackSize > g_maxStackSize )
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

        outString.append( buff );
        ++outputStackSize;
    }
}

MemoryTracker::~MemoryTracker()
{
}

NAMESPACE_END( CUL )