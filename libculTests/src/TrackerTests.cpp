#include "TrackerTests.hpp"
#include "CUL/Log/ILogger.hpp"
#include "Memory/MemoryTracker.hpp"

TrackerTests::TrackerTests()
{
}

TEST_F( TrackerTests, firstOne )
{
    CUL::MemoryTracker& mt = CUL::MemoryTracker::getInstance();
    mt.logAlloc((void*)10, 10u);
}

TEST_F( TrackerTests, secondOne )
{
}