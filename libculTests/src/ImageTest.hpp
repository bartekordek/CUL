#pragma once

#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class ImageTest: public ::testing::Test
{
protected:
    ImageTest();

    virtual ~ImageTest()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif