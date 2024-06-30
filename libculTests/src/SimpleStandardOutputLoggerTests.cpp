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
    CUL::LOG::ILogger& logger = CUL::LOG::ILogger::getInstance();
    logger.log( "Hello!" );
}