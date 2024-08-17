#include "TrackerTests.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/Memory/MemoryTracker.hpp"
#include "CUL/Memory/MemoryUtils.hpp"
#include "CUL/ITimer.hpp"

TrackerTests::TrackerTests()
{
#if defined( CUL_STATIC )
    CUL::MemoryTracker::getInstance().init();
#endif  // #if defined( CUL_STATIC )
}

void TrackerTests::SetUp()
{
}

void TrackerTests::TearDown()
{
}

TEST_F( TrackerTests, firstOne )
{
#if defined( CUL_STATIC )
    CUL::MemoryTracker& mt = CUL::MemoryTracker::getInstance();

    mt.toggleTracking( true );

    std::uint64_t* testValue = new std::uint64_t;

    while( mt.getActiveAllocations() == 0 )
    {
        CUL::ITimer::sleepMiliSeconds( 1 );
    }

    mt.dumpActiveAllocations();

    delete testValue;
    mt.dumpActiveAllocations();
    mt.toggleTracking( false );
#endif // #if defined( CUL_STATIC )
}

TEST_F( TrackerTests, secondOne )
{
}