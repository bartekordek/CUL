#include "CUL/Hardware/DiskInfo.hpp"
#include "CUL/IMPORT_windows.hpp"
#include "CUL/Log/ILogger.hpp"
#include "Hardware/DiskInfoWindows.hpp"
#include "Hardware/DiskInfoDummy.hpp"
#include <CUL/Messaging/MessageSystem.hpp>
#include <CUL/Filesystem/IFile.hpp>
#include <CUL/STL_IMPORTS/STD_algorithm.hpp>
#include <CUL/STL_IMPORTS/STD_mutex.hpp>

#undef max

namespace CUL
{
CDiskInfo& CDiskInfo::getInstance()
{
#if defined( CUL_WINDOWS )
    static CDiskInfoWindows s_instance;
#else
    static CDiskInfoDummy s_instance;
#endif  // #if defined(CUL_WINDOWS)

    return s_instance;
}

void CDiskInfo::setPoolIntervalMs( std::uint32_t inIntervalMs )
{
    m_poolIntervalMs = inIntervalMs == 0u ? 1u : inIntervalMs;
    onSampleWindowChanged();
}

void CDiskInfo::onSampleWindowChanged()
{
}

CDiskInfo::CDiskInfo()
{
    CUL::MessageSystem<CUL::SBigMD5FileCalc>::getInstance().registerHandler(
        &CDiskInfo::onMsgReceived, this );
}

void CDiskInfo::getDiskTasks( [[maybe_unused]] const StringWr& diskName ) const
{
}

void CDiskInfo::onMsgReceived( const SBigMD5FileCalc& inMsg )
{
    const FS::Path path( inMsg.Path );
    const auto& diskName = path.getDiskName();

    FileInfoContainer* container{ nullptr };
    {
        std::shared_lock readLock( m_filesInfosMtx );
        auto it = m_filesInfos.find( diskName );
        if( it != m_filesInfos.end() )
        {
            container = &it->second;
        }
    }

    if( !container )
    {
        std::unique_lock writeLock( m_filesInfosMtx );
        container = &m_filesInfos[diskName];
    }

    container->add( inMsg );
}

std::once_flag g_onceFlag;

void CDiskInfo::start( bool withDebugInfo )
{
    std::call_once( g_onceFlag, &CDiskInfo::initialize, this, withDebugInfo );

    m_run = true;
    m_mainThread.run();
    if( withDebugInfo )
    {
        m_debugInfoThread.run();
    }
}

void CDiskInfo::initialize( bool withDebugInfo )
{
    m_mainThread.setBody(
        [this]()
        {
            mainLoop();
        } );

    if( withDebugInfo )
    {
        m_debugInfoThread.setBody(
            [this]()
            {
                debugLoop();
            } );
    }
}

bool CDiskInfo::isMainLoopRunning() const
{
    return m_run;
}

std::uint32_t CDiskInfo::getPoolIntervalMs() const
{
    return m_poolIntervalMs == 0u ? 1u : m_poolIntervalMs;
}

std::size_t CDiskInfo::getSamplesPerAverage() const
{
    const std::uint32_t intervalMs = getPoolIntervalMs();
    if( intervalMs >= AverageWindowMs )
    {
        return 1u;
    }
    return static_cast<std::size_t>( AverageWindowMs / intervalMs );
}

std::uint32_t CDiskInfo::getAverageWindowMs() const
{
    return static_cast<std::uint32_t>( getSamplesPerAverage() ) * getPoolIntervalMs();
}

void CDiskInfo::getInfo()
{
}

std::vector<StringWr> CDiskInfo::getDisksNames() const
{
    return std::vector<StringWr>();
}

CDiskInfo::~CDiskInfo()
{
    m_run = false;
    m_mainThread.waitForCompletion();
}

void FileInfoContainer::add( const SBigMD5FileCalc& fileCalc )
{
    if( std::holds_alternative<bool>( fileCalc.Progress ) &&
        ( std::get<bool>( fileCalc.Progress ) == true ) )
    {
        // Remove info, file calculated.
        std::unique_lock writeLock( m_filesInfosMtx );
        auto it = m_filesInfo.find( fileCalc.Path.getValue() );
        if( it != m_filesInfo.end() )
        {
            m_filesInfo.erase( it );
        }
        return;
    }
    std::unique_lock writeLock( m_filesInfosMtx );
    m_filesInfo[fileCalc.Path.getValue()] = std::make_unique<SBigMD5FileCalc>( fileCalc );
}

std::vector<StringWr> FileInfoContainer::getStatusList() const
{
    StringWr temp;

    std::vector<StringWr> result;
    std::shared_lock readLock( m_filesInfosMtx );
    for( const auto& [path, fileInfo] : m_filesInfo )
    {
        temp = StringWr::createFromPrintf(
            CUL_STR( "%s: %3.2f%%" ), path.getCharVal(), fileInfo->percentage );
        result.push_back( temp );
    }
    return result;
}

std::vector<StringWr> CDiskInfo::getCurrentFiles( const StringWr& inDiskName ) const
{
    std::vector<StringWr> result;

    const FileInfoContainer* container{ nullptr };
    {
        std::shared_lock readLock( m_filesInfosMtx );
        const auto it = m_filesInfos.find( inDiskName );
        if( it != m_filesInfos.end() )
        {
            container = &it->second;
        }
    }

    if( container )
    {
        result = container->getStatusList();
    }

    return result;
}
}  // namespace CUL
