#include "DumbPtrTests.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

int gval = 0;

struct Base
{
    Base()
    {
        ++gval;
    }

    virtual ~Base()
    {
        --gval;
    }
};

struct Derived:
    public Base
{
    Derived()
    {
        ++gval;
    }

    virtual ~Derived()
    {
        --gval;
    }
};

using DumbPtr = CUL::GUTILS::DumbPtr<Base>;

DumbPtrTests::DumbPtrTests()
{
}

DumbPtrTests::~DumbPtrTests()
{
}

void DumbPtrTests::SetUpTestCase()
{
}

void DumbPtrTests::TearDownTestCase()
{
}

TEST_F( DumbPtrTests, genericTest )
{
    Base* ptr = new Derived();
    {
        DumbPtr dumbPtr;
        dumbPtr = ptr;
    }
    GTEST_ASSERT_EQ( 0, gval );
}