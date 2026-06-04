#pragma once

#include "Gtest.hpp"

#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_bitset.hpp"

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif

class MathTests: public ::testing::Test
{
protected:
    MathTests();

    virtual ~MathTests()
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