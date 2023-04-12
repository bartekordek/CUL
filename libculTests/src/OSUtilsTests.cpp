#include "CUL/OSUtils/ISystemFonts.hpp"
#include "OSUtilsTests.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

using ISystemFonts = CUL::OSUtils::ISystemFonts;

CUL::GUTILS::DumbPtr<CUL::CULInterface> OSUtilsTests::m_culInterface = nullptr;

OSUtilsTests::OSUtilsTests()
{
}

void OSUtilsTests::SetUpTestCase()
{
    m_culInterface = CUL::CULInterface::getInstance();
}

void OSUtilsTests::SetUp()
{
}

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4189 )
#endif
TEST_F( OSUtilsTests, genericCreation )
{
#if _WIN32 //TODO LINUX:
    auto sf = m_culInterface->getSystemFonts();
    GTEST_ASSERT_EQ( sf != nullptr, true );
    auto& ff = sf->getFontFilesPaths();
    GTEST_ASSERT_GT( ff.size(), 0 );
#endif
}

void OSUtilsTests::TearDown()
{
}

void OSUtilsTests::TearDownTestCase()
{
    m_culInterface.release();
}

OSUtilsTests::~OSUtilsTests()
{
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif