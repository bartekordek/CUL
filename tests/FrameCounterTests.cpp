#include "FrameCounterTests.hpp"
#include "CUL/Video/IFPSCounter.hpp"
#include "CUL/ITimer.hpp"

using namespace CUL;
using namespace Video;

FrameCounterTests::FrameCounterTests( void )
{

}

FrameCounterTests::~FrameCounterTests( void )
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
    fpsCounter->start();
    fpsCounter->stop();
    GTEST_ASSERT_EQ( 0, static_cast<unsigned>( fpsCounter->getCurrentFps() ) );
}

TEST_F( FrameCounterTests, fpsAverageCountShouldBe0 )
{
    auto fpsCounter = FPSCounterFactory::getConcreteFPSCounter();
    std::unique_ptr<IFPSCounter> fpsCounterPtr( fpsCounter );
    fpsCounter->start();
    fpsCounter->stop();
    auto avgFps = static_cast<unsigned>( fpsCounter->getAverageFps() );
    GTEST_ASSERT_EQ( 0, avgFps );
}

TEST_F( FrameCounterTests, fpsCurrentCountShouldBe10 )
{
    auto fpsCounter = FPSCounterFactory::getConcreteFPSCounter();
    std::unique_ptr<IFPSCounter> fpsCounterPtr( fpsCounter );
    fpsCounter->start();
    for( unsigned int i = 0; i < 10; ++i )
    {
        fpsCounter->increase();
    }
    fpsCounter->stop();
    auto fpsCount = fpsCounter->getCurrentFps();
    auto avgFps = static_cast< unsigned >( fpsCount );
    GTEST_ASSERT_EQ( 10, avgFps );
}

TEST_F( FrameCounterTests, fpsAverageCountShouldBe10 )
{
    auto fpsCounter = FPSCounterFactory::getConcreteFPSCounter();
    std::unique_ptr<IFPSCounter> fpsCounterPtr( fpsCounter );
    fpsCounter->start();
    for( unsigned int i = 0; i < 10; ++i )
    {
        fpsCounter->increase();
    }
    ITimer::sleepMiliSeconds( 1200 );
    fpsCounter->stop();
    auto fpsCount = fpsCounter->getAverageFps();
    auto avgFps = static_cast< unsigned >(fpsCount);
    GTEST_ASSERT_EQ( 5, avgFps );
}