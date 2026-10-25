#pragma once

#include "CUL/Threading/ThreadWrap.hpp"
#include <CUL/Messaging/FSMessages.hpp>
#include "CUL/Math/VariableWithAverageValue.hpp"
#include <CUL/GenericUtils/NonCopyable.hpp>
#include <CUL/STL_IMPORTS/STD_memory.hpp>
#include <CUL/STL_IMPORTS/STD_shared_mutex.hpp>
#include <CUL/STL_IMPORTS/STD_unordered_map.hpp>
#include <CUL/STL_IMPORTS/STD_unordered_set.hpp>

namespace CUL
{
class FileInfoContainer
{
public:
    FileInfoContainer() = default;

    void add( const SBigMD5FileCalc& fileCalc );

    std::vector<StringWr> getStatusList() const;

    CUL_NONCOPYABLE( FileInfoContainer )

    ~FileInfoContainer() = default;

private:
    std::unordered_map<StringWr, std::unique_ptr<SBigMD5FileCalc>> m_filesInfo;
    mutable std::shared_mutex m_filesInfosMtx;
};

class CULLib_API CDiskInfo
{
public:
    static CDiskInfo& getInstance();
    void setPoolIntervalMs( std::uint32_t inIntervalMs );
    void start( bool withDebugInfo = false );
    void getInfo();
    virtual std::vector<std::pair<std::string, float>> getDisksUsage() const = 0;
    virtual float getDiskUsage( const std::string& inDiskName ) const = 0;
    virtual std::vector<StringWr> getDisksNames() const;

    void getDiskTasks( const StringWr& diskName ) const;
    std::vector<StringWr> getCurrentFiles( const StringWr& inDiskName ) const;
    std::uint32_t getPoolIntervalMs() const;
    // Busy % is the mean of samples inside this window. Callers that wait on
    // getDiskUsage() should sleep one window so the next read is a new average.
    std::uint32_t getAverageWindowMs() const;
    std::size_t getSamplesPerAverage() const;

    // One sample spans many HDD commands (seek is ~10 ms). 250 ms is a duty
    // cycle, not a single I/O. The 1 s window is the scheduler wait.
    static constexpr std::uint32_t DefaultPoolIntervalMs = 250u;
    static constexpr std::uint32_t AverageWindowMs = 1000u;

protected:
    CDiskInfo();
    ~CDiskInfo();
    bool isMainLoopRunning() const;
    virtual void onSampleWindowChanged();

private:
    void initialize( bool withDebugInfo );
    void onMsgReceived( const SBigMD5FileCalc& inMsg );

    virtual void findDiskMappings() = 0;
    virtual void mainLoop() = 0;
    virtual void debugLoop() = 0;

    bool m_run{ false };
    std::uint32_t m_poolIntervalMs{ DefaultPoolIntervalMs };
    ThreadWrapper m_mainThread;
    ThreadWrapper m_debugInfoThread;
    MATH::VariableWithAverageValue m_percentageAverage;

    std::unordered_map<StringWr, FileInfoContainer> m_filesInfos;
    mutable std::shared_mutex m_filesInfosMtx;

    CUL_NONCOPYABLE( CDiskInfo )
};

}  // namespace CUL
