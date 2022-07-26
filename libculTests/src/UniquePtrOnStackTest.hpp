#pragma once

#include "Gtest.hpp"

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif

namespace UniquePtrOnStackTest
{

struct Base
{
    Base();

    virtual ~Base();
};

struct Derived: public Base
{
    Derived();

    virtual ~Derived();
};

class UniquePtrOnStack: public ::testing::Test
{
protected:
    UniquePtrOnStack();
    virtual ~UniquePtrOnStack();

    static void SetUpTestCase();
    static void TearDownTestCase();
};

}  // namespace UniquePtrOnStackTest

#ifdef _MSC_VER
#pragma warning( pop )
#endif