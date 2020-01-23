#include "FrameCounterTests.hpp"
#include "CUL/Video/IFPSCounter.hpp"
#include "CUL/ITimer.hpp"

using namespace CUL;
using namespace Video;

FrameCounterTests::FrameCounterTests()
{
}

FrameCounterTests::~FrameCounterTests()
{
}

void FrameCounterTests::SetUpTestCase()
{
}

void FrameCounterTests::TearDownTestCase()
{
}

TEST_F( FrameCounterTests, fpsCurrentCountShouldBe0 )
{
    auto fpsCounter = FPSCounterFactory::getConcreteFPSCounter();
    std::unique_ptr<IFPSCounter> fpsCounterPtr( fpsCounter );
    fpsCounter->setMeasurePeriod( measurePeriod );
    fpsCounter->start();
    fpsCounter->stop();
    GTEST_ASSERT_EQ( 0, static_cast<unsigned>( fpsCounter->getCurrentFps() ) );
}

TEST_F( FrameCounterTests, fpsAverageCountShouldBe0 )
{
    auto fpsCounter = FPSCounterFactory::getConcreteFPSCounter();
    std::unique_ptr<IFPSCounter> fpsCounterPtr( fpsCounter );
    fpsCounter->setMeasurePeriod( measurePeriod );
    fpsCounter->start();
    fpsCounter->stop();
    auto avgFps = static_cast<unsigned>( fpsCounter->getAverageFps() );
    GTEST_ASSERT_EQ( 0, avgFps );
}
#ifdef ALIENS_EXIST_TODO_IS_DONE
// Something is no yes here.
TEST_F( FrameCounterTests, fpsCurrentCountShouldBe10 )
{
    auto fpsCounter = FPSCounterFactory::getConcreteFPSCounter();
    std::unique_ptr<IFPSCounter> fpsCounterPtr( fpsCounter );
    fpsCounter->setMeasurePeriod( measurePeriod );
    fpsCounter->start();
    for( unsigned int i = 0; i < 10; ++i )
    {
        fpsCounter->increase();
    }
    fpsCounter->stop();
    auto fpsCount = fpsCounter->getCurrentFps();
    auto avgFps = static_cast<unsigned>( fpsCount );
    GTEST_ASSERT_EQ( 10, avgFps );
}

// TODO:
// Something is no yes here.
TEST_F( FrameCounterTests, fpsAverageCountShouldBe40 )
{
    const auto fpsTarget = 40;
    auto fpsCounter = FPSCounterFactory::getConcreteFPSCounter();
    std::unique_ptr<IFPSCounter> fpsCounterPtr( fpsCounter );
    fpsCounter->setMeasurePeriod( measurePeriod );
    fpsCounter->start();
    for( unsigned int i = 0; i < fpsTarget; ++i )
    {
        fpsCounter->increase();
    }
    fpsCounter->stop();
    auto fpsCount = fpsCounter->getAverageFps();
    auto avgFps = static_cast<unsigned>( fpsCount );
    GTEST_ASSERT_EQ( fpsTarget * 1000.0 / measurePeriod, avgFps );
}
#endif