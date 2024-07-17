#include "TrackerTests.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/Memory/MemoryTracker.hpp"
#include "CUL/Memory/MemoryUtils.hpp"

TrackerTests::TrackerTests()
{
}

TEST_F( TrackerTests, firstOne )
{
    CUL::MemoryTracker& mt = CUL::MemoryTracker::getInstance();

    mt.toggleTracking( true );

    std::uint64_t* testValue = new std::uint64_t;

    mt.dumpActiveAllocations();

    delete testValue;
    mt.dumpActiveAllocations();
    mt.toggleTracking( false );
}

TEST_F( TrackerTests, secondOne )
{
}