#pragma once

#include <CUL/Hardware/DiskInfo.hpp>

#if defined( CUL_WINDOWS )
#include <CUL/Math/VariableWithAverageValue.hpp>
#include <CUL/String.hpp>
#include <CUL/STL_IMPORTS/STD_unordered_map.hpp>
#include <CUL/STL_IMPORTS/STD_mutex.hpp>
#include <CUL/STL_IMPORTS/STD_cstdint.hpp>
#include "CUL/IMPORT_windows.hpp"


#pragma comment( lib, "Pdh.lib" )
#define CALCULATE_FROM_IDLE 1

namespace CUL
{

using VWAV = MATH::VWAV ;
struct SDiskInfo
{
#if CALCULATE_FROM_IDLE
#else // CALCULATE_FROM_IDLE
    std::int64_t ReadBytes{ 0 };
    std::int64_t ReadTime{ 0 };

    std::int64_t WriteBytes{ 0 };
    std::int64_t WriteTime{ 0 };
#endif // CALCULATE_FROM_IDLE
};

struct DiskInfoValue
{
    void* Handle{ nullptr };
    std::string Name;
#if CALCULATE_FROM_IDLE
    std::int64_t PreviousIdle{ 0 };
    std::int64_t CurrentIdleTime{ 0 };
    std::int64_t Delta{ 0 };
    VWAV IdleTime;
    VWAV PercentageUsed;
#else // CALCULATE_FROM_IDLE
    SDiskInfo Last;
    SDiskInfo Current;
    SDiskInfo Delta;
    VWAV BytesPerSecondRead;
    VWAV BytesPerSecondWrite;
#endif // CALCULATE_FROM_IDLE
};

class CDiskInfoWindows final: public CDiskInfo
{
public:
    CDiskInfoWindows();

    ~CDiskInfoWindows();

protected:
private:
    void findDiskMappings() override;
    void mainLoop() override;
    void debugLoop() override;
    float getDiskUsage( const std::string& inDiskName ) const override;

    void collectData( DiskInfoValue& inOutData );

    mutable std::mutex m_diskHandlesMtx;
    std::unordered_map<std::string, DiskInfoValue> m_diskHandles;
    LARGE_INTEGER m_ticksPerSeconds{ 0 };

public:
    CUL_NONCOPYABLE( CDiskInfoWindows );
};

}  // namespace CUL

#endif  // #if defined(CUL_WINDOWS)