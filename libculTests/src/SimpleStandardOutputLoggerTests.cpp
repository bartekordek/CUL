#include "SimpleStandardOutputLoggerTests.hpp"
#include "CUL/Log/ILogger.hpp"

SimpleStandardOutputLoggerTests::SimpleStandardOutputLoggerTests()
{
}

SimpleStandardOutputLoggerTests::~SimpleStandardOutputLoggerTests()
{
}

void SimpleStandardOutputLoggerTests::SetUpTestCase()
{
}

void SimpleStandardOutputLoggerTests::TearDownTestCase()
{
}

TEST_F( SimpleStandardOutputLoggerTests, genericTest )
{
    const auto logger = CUL::LOG::ILogger::createSimpleStandardOutputLogger();
    GTEST_ASSERT_EQ( false, logger == nullptr );
    logger->log( "Hello!" );
}