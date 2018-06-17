#pragma once

#include "CUL/MyString.hpp"

#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class NameTests:
    public ::testing::Test
{
protected:
    NameTests()
    {
    }

    virtual ~NameTests()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
    CUL::MyString genericName = CUL::MyString( "Generic name." );
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif