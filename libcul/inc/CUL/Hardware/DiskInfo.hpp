#pragma once

#include "CUL/Threading/ThreadWrap.hpp"
#include "CUL/Math/VariableWithAverageValue.hpp"
#include <CUL/GenericUtils/NonCopyable.hpp>

namespace CUL
{
class CULLib_API CDiskInfo
{
public:
    static CDiskInfo& getInstance();
    void setPoolIntervalMs( std::uint32_t inIntervalMs );
    void start( bool withDebugInfo = false );
    void getInfo();
    virtual std::vector<std::pair<std::string, float>> getDisksUsage() const = 0;
    virtual float getDiskUsage( const std::string& inDiskName ) const = 0;

protected:
    CDiskInfo();
    ~CDiskInfo();
    bool isMainLoopRunning() const;
    std::uint32_t getPoolIntervalMs() const;

private:
    void initialize( bool withDebugInfo );
    virtual void findDiskMappings() = 0;
    virtual void mainLoop() = 0;
    virtual void debugLoop() = 0;

    bool m_run{ false };
    std::uint32_t m_poolIntervalMs{ 200u };
    ThreadWrapper m_mainThread;
    ThreadWrapper m_debugInfoThread;
    MATH::VariableWithAverageValue m_percentageAverage;

    CUL_NONCOPYABLE( CDiskInfo )
};

}
