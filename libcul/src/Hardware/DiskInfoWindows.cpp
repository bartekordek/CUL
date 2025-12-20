#include "Hardware/DiskInfoWindows.hpp"

#if defined( CUL_WINDOWS )
#include "CUL/Log/ILogger.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/IMPORT_windows.hpp"
#include <CUL/STL_IMPORTS/STD_algorithm.hpp>

#pragma comment( lib, "Pdh.lib" )

#define PDH_IMPL 0
#define IOCTL 1

using namespace CUL;

CDiskInfoWindows::CDiskInfoWindows()
{
    BOOL rc = QueryPerformanceFrequency( &m_ticksPerSeconds );

    findDiskMappings();
}

void CDiskInfoWindows::findDiskMappings()
{
    constexpr static std::size_t bufferLength = 8u;
    char buffer[bufferLength];

    constexpr float TimeCoverageMs = 4.f * 1000.f;
    const float howManySamples = TimeCoverageMs / getPoolIntervalMs();

    for (char currentDiskName = 'A'; currentDiskName <= 'Z'; ++currentDiskName)
    {
        snprintf( buffer, bufferLength, "\\\\.\\%c:", currentDiskName );
        HANDLE hTarget = CreateFile( buffer, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL );
        if( hTarget != INVALID_HANDLE_VALUE )
        {
            DiskInfoValue di;
            di.Handle = hTarget;
            di.Name.push_back( currentDiskName );
            di.Name.push_back(':');
#if CALCULATE_FROM_IDLE
            di.IdleTime.setCapacity( static_cast<std::size_t>( howManySamples ) );
#else // CALCULATE_FROM_IDLE
            di.BytesPerSecondRead.setCapacity( static_cast<std::size_t>( howManySamples ) );
            di.BytesPerSecondWrite.setCapacity( static_cast<std::size_t>( howManySamples ) );
#endif // CALCULATE_FROM_IDLE
            di.PercentageUsed.setCapacity( howManySamples );

            m_diskHandles[di.Name] = di;
        }
    }

    // HANDLE hTarget = CreateFile( "D:", 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL );

    // DISK_PERFORMANCE dp = { 0 };
    // DWORD cbOutBufferSize = sizeof( DISK_PERFORMANCE );
    // DWORD cbBytesReturned = 0;
    // LPVOID lpOutBuffer = (LPVOID)&dp;

    // if( !DeviceIoControl( hTarget, IOCTL_DISK_PERFORMANCE, NULL, 0, lpOutBuffer, cbOutBufferSize, &cbBytesReturned, NULL ) )
    //{
    //     CloseHandle( hTarget );
    //     return;
    // }
    // else
    //{
    //     CloseHandle( hTarget );
    //     const auto part = dp.BytesRead.QuadPart;
    // }

#if PDH_IMPL
    HANDLE hPdhLibrary = NULL;
    LPWSTR pMessage = NULL;
    DWORD dwErrorCode = PDH_PLA_ERROR_ALREADY_EXISTS;
    hPdhLibrary = LoadLibrary( "pdh.dll" );
#endif  // PDH_IMPL

#if PDH_IMPL
    PDH_HQUERY diskQuery;
    PDH_STATUS status = PdhOpenQuery( NULL, 0, &diskQuery );
    PDH_HCOUNTER diskTime;
    PDH_FMT_COUNTERVALUE diskTimeVal;
    PdhAddCounter( diskQuery, TEXT( "\\PhysicalDisk(0 D:)\\% Read Time" ), 0, &diskTime );

    while( m_run )
    {
        PdhCollectQueryData( diskQuery );
        PdhGetFormattedCounterValue( diskTime, PDH_FMT_DOUBLE, NULL, &diskTimeVal );
        const float percentage = diskTimeVal.doubleValue;
        m_percentageAverage.add( percentage );
        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "Disk: %f", percentage );
        ITimer::sleepMiliSeconds( 1000u );
    }
    PdhCloseQuery( diskQuery );
#elif IOCTL
    std::string diskInfo{ "D:" };

//#define wszDrive "\\\\.\\PhysicalDrive1"
//#define wszDrive2 "\\\\.\\D:"
//    HANDLE hTarget = CreateFile( wszDrive, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL );
//    
//    if( hTarget == INVALID_HANDLE_VALUE )
//    {
//        const auto error = GetLastError();
//        return;
//    }
//
//
//
//    if( !DeviceIoControl( hTarget, IOCTL_DISK_PERFORMANCE, NULL, 0, lpOutBuffer, cbOutBufferSize, &cbBytesReturned, NULL ) )
//    {
//        CloseHandle( hTarget );
//        return;
//    }
//
//
//
//    std::int64_t maxDiff = 0;
//
//
//    if( !DeviceIoControl( hTarget, IOCTL_DISK_PERFORMANCE, NULL, 0, lpOutBuffer, cbOutBufferSize, &cbBytesReturned, NULL ) )
//    {
//        CloseHandle( hTarget );
//    }
//    else
//    {
//        CloseHandle( hTarget );
//        const auto XD = dp.BytesRead.QuadPart;
//    }
#endif  // PDH_IMPL
}

void CDiskInfoWindows::mainLoop()
{
    while( isMainLoopRunning() )
    {
        {
            std::lock_guard<std::mutex> locker( m_diskHandlesMtx );
            for( auto& [name, diskInfo] : m_diskHandles )
            {
                collectData( diskInfo );
            }
        }

        //if( !DeviceIoControl( hTarget, IOCTL_DISK_PERFORMANCE, NULL, 0, lpOutBuffer, cbOutBufferSize, &cbBytesReturned, NULL ) )
        //{
        //    CloseHandle( hTarget );
        //    break;
        //}

        //const std::int64_t wt = dp.WriteTime.QuadPart;
        //const std::int64_t it = dp.IdleTime.QuadPart;

        //const auto diffWt = wt - prevWt;
        //const auto diffIt = it - prevIt;

        //maxDiff = std::max( maxDiff, diffIt );

        //LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "Write time diff: %lu, IdleTime diff %lu [%lu]", diffWt, diffIt,
        //                                         maxDiff );
        //prevIt = it;
        //prevWt = wt;

        ITimer::sleepMiliSeconds( getPoolIntervalMs() );
    }   
}

constexpr float bytesInMegabyte = 1024.f * 1024.f;

void CDiskInfoWindows::debugLoop()
{
    while( isMainLoopRunning() )
    {
        ITimer::sleepMiliSeconds( 4000u );
        std::unordered_map<std::string, DiskInfoValue> diskInfos;
        {
            std::lock_guard<std::mutex> locker( m_diskHandlesMtx );
            diskInfos = m_diskHandles;
        }

        LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "\nDiskData:" );
        for( const std::pair<std::string, DiskInfoValue> diskInfoValue : diskInfos )
        {
            const DiskInfoValue& di = diskInfoValue.second;
            const float percentage = di.PercentageUsed.getAverage();
            LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "Disk: %s, Usage: %f%%)",
                                                     diskInfoValue.first.c_str(), percentage );
#if CALCULATE_FROM_IDLE
#else // CALCULATE_FROM_IDLE
            const float megabytesWrite = di.BytesPerSecondWrite.getAverage() / bytesInMegabyte;
            const float megabytesRead = di.BytesPerSecondRead.getAverage() / bytesInMegabyte;

            const float megabytesWriteMax = di.BytesPerSecondWrite.getMax() / bytesInMegabyte;
            const float megabytesReadMax = di.BytesPerSecondRead.getMax() / bytesInMegabyte;

            const float percentageWrite = 100.f * megabytesWrite / megabytesWriteMax;
            const float percenttageRead = 100.f * megabytesRead / megabytesReadMax;
            LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "Disk: %s, Read: %f MB (%f%%), Write: %f MB (%f%%)",
                                                     diskInfoValue.first.c_str(), megabytesRead, percenttageRead, megabytesWrite,
                                                     percentageWrite );
#endif  // CALCULATE_FROM_IDLE
            //const auto writeMax = di.BytesWritten.getMax();
            //const auto readMax = di.BytesRead.getMax();

            //const auto writeAvg = di.BytesWritten.getAverage();
            //const auto readAvg = di.BytesRead.getAverage();


            //const float maxDiskIOvalues = static_cast<float>( writeMax + readMax );
            //const float averageIoValues = static_cast<float>( writeAvg + readAvg );
            //const float percentage = 100.f * averageIoValues / maxDiskIOvalues;


            //LOG::ILogger::getInstance().logVariable( LOG::Severity::Info, "Disk: %s: %f", diskInfoValue.first.c_str(), percentage );
        }
    }
}

SDiskInfo calcDelta( const SDiskInfo& v1, const SDiskInfo& v2 )
{
    SDiskInfo result;

#if CALCULATE_FROM_IDLE
#else // #if CALCULATE_FROM_IDLE
    result.WriteBytes = v1.WriteBytes - v2.WriteBytes;
    result.ReadBytes = v1.ReadBytes - v2.ReadBytes;

    result.WriteTime = v1.WriteTime - v2.WriteTime;
    result.ReadTime = v1.ReadTime - v2.ReadTime;
#endif // #if CALCULATE_FROM_IDLE

    return result;
}


void CDiskInfoWindows::collectData( DiskInfoValue& inOutDataValue )
{
    DISK_PERFORMANCE dp = { 0 };
    DWORD cbOutBufferSize = sizeof( DISK_PERFORMANCE );
    DWORD cbBytesReturned = 0;
    LPVOID lpOutBuffer = (LPVOID)&dp;

#if CALCULATE_FROM_IDLE
#else // #if CALCULATE_FROM_IDLE
    inOutDataValue.Last = inOutDataValue.Current;
#endif // #if CALCULATE_FROM_IDLE

    if( DeviceIoControl( inOutDataValue.Handle, IOCTL_DISK_PERFORMANCE, NULL, 0, lpOutBuffer, cbOutBufferSize, &cbBytesReturned, NULL ) )
    {
#if CALCULATE_FROM_IDLE
        inOutDataValue.PreviousIdle = inOutDataValue.CurrentIdleTime;
        inOutDataValue.CurrentIdleTime = dp.IdleTime.QuadPart;
        inOutDataValue.Delta = inOutDataValue.CurrentIdleTime - inOutDataValue.PreviousIdle;

        inOutDataValue.IdleTime.add( static_cast<float>( inOutDataValue.Delta ) );

        float percentage;
        if( static_cast<std::int64_t>( inOutDataValue.IdleTime.getMax() ) == 0 )
        {
            percentage = 100.f;
        }
        else
        {
            percentage = 100.f * ( 1.f - ( inOutDataValue.IdleTime.getAverage() / inOutDataValue.IdleTime.getMax() ) );
        }

        inOutDataValue.PercentageUsed.add( percentage );
#else // #if CALCULATE_FROM_IDLE
        SDiskInfo& current = inOutDataValue.Current;
        current.ReadBytes = dp.BytesRead.QuadPart;
        current.WriteBytes = dp.BytesWritten.QuadPart;
        current.ReadTime = dp.ReadTime.QuadPart;
        current.WriteTime = dp.WriteTime.QuadPart;


        SDiskInfo& last = inOutDataValue.Last;
        inOutDataValue.Delta = last;


        VWAV& bpsr = inOutDataValue.BytesPerSecondRead;
        VWAV& bpsw = inOutDataValue.BytesPerSecondWrite;

        SDiskInfo& delta = inOutDataValue.Delta;

        float bpsrf{ 0.f };
        float bpswf{ 0.f };
        if( delta.ReadTime != 0 )
        {
            bpsrf = static_cast<float>( m_ticksPerSeconds.QuadPart ) * delta.ReadBytes / delta.ReadTime;
            
        }

        if( delta.WriteTime != 0 )
        {
            bpswf = static_cast<float>( m_ticksPerSeconds.QuadPart ) * delta.WriteBytes / delta.WriteTime;
        }

        bpsr.add( bpsrf );
        bpsw.add( bpswf );
#endif  // #if CALCULATE_FROM_IDLE
    }
}

float CDiskInfoWindows::getDiskUsage( const std::string& inDiskName ) const
{
    std::unordered_map<std::string, DiskInfoValue> diskInfos;
    {
        std::lock_guard<std::mutex> locker( m_diskHandlesMtx );
        diskInfos = m_diskHandles;
    }

    const auto it = diskInfos.find( inDiskName );
    if( it == diskInfos.end() )
    {
        return 0.f;
    }

    const DiskInfoValue& di = it->second;
#if CALCULATE_FROM_IDLE
    const float result = di.PercentageUsed.getAverage();
    return result;
#else // CALCULATE_FROM_IDLE
    const float megabytesWrite = di.BytesPerSecondWrite.getAverage() / bytesInMegabyte;
    const float megabytesRead = di.BytesPerSecondRead.getAverage() / bytesInMegabyte;

    const float megabytesWriteMax = di.BytesPerSecondWrite.getMax() / bytesInMegabyte;
    const float megabytesReadMax = di.BytesPerSecondRead.getMax() / bytesInMegabyte;

    const float percentageWrite = 100.f * megabytesWrite / megabytesWriteMax;
    const float percenttageRead = 100.f * megabytesRead / megabytesReadMax;

    return ( percentageWrite + percenttageRead ) / 2.f;
#endif // CALCULATE_FROM_IDLE
}

std::vector<std::pair<std::string, float>> CDiskInfoWindows::getDisksUsage() const
{
    std::vector<std::pair<std::string, float>> result;

    {
        std::lock_guard<std::mutex> locker( m_diskHandlesMtx );
        for( auto& [_, diskValue] : m_diskHandles )
        {
            std::pair<std::string, float> valuePair;
            valuePair.first = diskValue.Name;
            valuePair.second = diskValue.PercentageUsed.getAverage();
            result.push_back( valuePair );
        }
    }
    std::sort( result.begin(), result.end(),
               []( const std::pair<std::string, float>& p1, const std::pair<std::string, float>& p2 )
               {
                   return p1.first < p2.first;
               } );

    return result;
}

CDiskInfoWindows::~CDiskInfoWindows()
{
}

#endif  // #if defined(CUL_WINDOWS)