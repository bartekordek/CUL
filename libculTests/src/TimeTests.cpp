#include "TimeTests.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/Time.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

using namespace CUL;

TimeTests::TimeTests()
{
}

TimeTests::~TimeTests()
{
}

void TimeTests::SetUpTestCase()
{
}

void TimeTests::TearDownTestCase()
{
}

TEST_F( TimeTests, MeasureTime )
{
    CUL::LOG::ILogger& logger = CUL::LOG::ILogger::getInstance();
    auto timer = std::unique_ptr<ITimer>( TimerFactory::getChronoTimerPtr( &logger ) );
    timer->start();
    unsigned ms2Sleep = 1000;
    ITimer::sleepMiliSeconds( ms2Sleep );
    auto& el = timer->getElapsed();
    GTEST_ASSERT_GE( el.getMs(), ms2Sleep );
}

TEST_F( TimeTests, Reset )
{
    CUL::LOG::ILogger& logger = CUL::LOG::ILogger::getInstance();
    auto timer = std::unique_ptr<ITimer>( TimerFactory::getChronoTimerPtr( &logger ) );
    timer->start();
    unsigned ms2Sleep = 1000;
    ITimer::sleepMiliSeconds( ms2Sleep );
    auto& el1 = timer->getElapsed();
    GTEST_ASSERT_GE( el1.getMs(), ms2Sleep );
    timer->reset();
    auto& el2 = timer->getElapsed();
    GTEST_ASSERT_LE( el2.getMs(), ms2Sleep / 2 );
}

TEST_F( TimeTests, Diff )
{
    const Time time1( 0, 1, 1, 0, 1, 0 );
    const Time time2( 0, 1, 1, 0, 0, 59 );

    const auto diff = time1 - time2;

    GTEST_ASSERT_EQ( diff.Year, 0 );
    GTEST_ASSERT_EQ( diff.Month, 0 );
    GTEST_ASSERT_EQ( diff.Day, 0 );
    GTEST_ASSERT_EQ( diff.Hour, 0 );
    GTEST_ASSERT_EQ( diff.Minute, 0 );
    GTEST_ASSERT_EQ( diff.Seconds, 1 );
}