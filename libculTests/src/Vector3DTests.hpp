#pragma once

#include "Gtest.hpp"
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#pragma warning( disable: 5045 )
#endif
class Vector3DTests: public ::testing::Test
{
public:
protected:
    Vector3DTests()
    {
    }

    virtual ~Vector3DTests()
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