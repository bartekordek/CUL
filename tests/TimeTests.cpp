#include "TimeTests.hpp"
#include "CUL/ITimer.hpp"
#include "CUL/STD_memory.hpp"

using namespace CUL;

TimeTests::TimeTests( void )
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
    auto timer = std::unique_ptr<ITimer>( TimerFactory::getChronoTimer() );
    timer->start();
    unsigned ms2Sleep = 1000;
    ITimer::sleepMiliSeconds( ms2Sleep );
    auto& el = timer->getElapsed();
    GTEST_ASSERT_GE( el.getMs(), ms2Sleep );
}

TEST_F( TimeTests, Reset )
{
    auto timer = std::unique_ptr<ITimer>( TimerFactory::getChronoTimer() );
    timer->start();
    unsigned ms2Sleep = 1000;
    ITimer::sleepMiliSeconds( ms2Sleep );
    auto& el1 = timer->getElapsed();
    GTEST_ASSERT_GE( el1.getMs(), ms2Sleep );
    timer->reset();
    auto& el2 = timer->getElapsed();
    GTEST_ASSERT_LE( el2.getMs(), ms2Sleep / 2 );
}