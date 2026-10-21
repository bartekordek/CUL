#include <CUL/Filesystem/DiskScheduler.hpp>
#include <CUL/Filesystem/Path.hpp>
#include <CUL/ITimer.hpp>
#include "CUL/Hardware/DiskInfo.hpp"
#include <CUL/Log/ILogger.hpp>
#include <CUL/STL_IMPORTS/STD_mutex.hpp>
#include <CUL/STL_IMPORTS/STD_unordered_map.hpp>
#include <CUL/STL_IMPORTS/STD_memory.hpp>
#include <CUL/STL_IMPORTS/STD_algorithm.hpp>
#include <cctype>

namespace CUL
{
namespace
{
constexpr float g_safeThreshold = 50.f;
// Wait at most this many average windows, then start so a busy listing cannot block hashing.
constexpr std::uint32_t g_maxAverageWindows = 2u;

std::string normalizeDiskKey( std::string diskName )
{
    if( diskName.empty() )
    {
        return diskName;
    }

    while( !diskName.empty() && ( diskName.back() == '\\' || diskName.back() == '/' ) )
    {
        diskName.pop_back();
    }

    if( diskName.size() >= 2 && diskName[1] == ':' )
    {
        diskName[0] = static_cast<char>( std::toupper( static_cast<unsigned char>( diskName[0] ) ) );
        return diskName.substr( 0, 2 );
    }

    return diskName;
}
}  // namespace

class CDiskScheduler_impl
{
public:
    CDiskScheduler_impl() = default;

    void executeWhenPossibleWithWait( const StringWr& inPath, std::function<void( void )> inFunction )
    {
        static thread_local auto timer = TimerFactory::getChronoTimerPtr( nullptr );

        const std::uint32_t averageWindowMs = std::max( 1u, CDiskInfo::getInstance().getAverageWindowMs() );
        const std::uint32_t maxWaitMs = averageWindowMs * g_maxAverageWindows;
        const FS::Path path( inPath );
        const std::string diskKey = normalizeDiskKey( path.getDiskName().getSTDString() );

        std::uint32_t waitedMs = 0u;
        float diskUsage = CDiskInfo::getInstance().getDiskUsage( diskKey );
        while( diskUsage >= g_safeThreshold && waitedMs < maxWaitMs )
        {
            timer->sleepMiliSeconds( averageWindowMs );
            waitedMs += averageWindowMs;
            diskUsage = CDiskInfo::getInstance().getDiskUsage( diskKey );
        }

        if( waitedMs >= maxWaitMs && diskUsage >= g_safeThreshold )
        {
            LOG::ILogger::getInstance().logVariable(
                LOG::Severity::Warn,
                "[CDiskScheduler] Disk %s still busy (%.1f%% >= %.1f%%) after %u ms; starting MD5 anyway.",
                diskKey.c_str(), diskUsage, g_safeThreshold, waitedMs );
        }

        // One big-file hash at a time per disk — do not serialize all disks on one global lock.
        std::lock_guard<std::mutex> locker( mutexForDisk( diskKey ) );
        inFunction();
    }

    static float getSafeThreshold()
    {
        return g_safeThreshold;
    }

    CUL_NONCOPYABLE( CDiskScheduler_impl );
    ~CDiskScheduler_impl() = default;

private:
    std::mutex& mutexForDisk( const std::string& diskKey )
    {
        std::lock_guard<std::mutex> locker( m_registryMtx );
        auto& slot = m_diskMutexes[diskKey];
        if( !slot )
        {
            slot = std::make_unique<std::mutex>();
        }
        return *slot;
    }

    std::mutex m_registryMtx;
    std::unordered_map<std::string, std::unique_ptr<std::mutex>> m_diskMutexes;
};

CDiskScheduler& CDiskScheduler::getInstance()
{
    static CDiskScheduler s_instance;
    return s_instance;
}

CDiskScheduler::CDiskScheduler()
    : m_impl( std::make_unique<CDiskScheduler_impl>() )
{
}

void CDiskScheduler::executeWhenPossibleWithWait( const StringWr& inPath, std::function<void( void )> inFunction )
{
    m_impl->executeWhenPossibleWithWait( inPath, inFunction );
}

float CDiskScheduler::getSafeThresholdPercent()
{
    return CDiskScheduler_impl::getSafeThreshold();
}

CDiskScheduler::~CDiskScheduler()
{
}
}  // namespace CUL
