#include "CUL/OSUtils/ISystemFonts.hpp"
#include "OSUtilsTests.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

using ISystemFonts = CUL::OSUtils::ISystemFonts;

OSUtilsTests::OSUtilsTests( void )
{
}

OSUtilsTests::~OSUtilsTests( void )
{
}

void OSUtilsTests::SetUpTestCase()
{
}

void OSUtilsTests::TearDownTestCase()
{
}

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4189 )
#endif
TEST_F( OSUtilsTests, genericCreation )
{
    auto ptr = CUL::OSUtils::getUtil();
    if( ptr )
    {
        std::unique_ptr<ISystemFonts> sf( ptr );
        auto& ff = sf->getFontFilesPaths();
        GTEST_ASSERT_GT( ff.size(), 0 );
    }
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif