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
    m_culInterface = CUL::CULInterface::createInstance();
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
// TODO:
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