#include "LockPrimTests.hpp"
#include "CUL/LckPrim.hpp"

TEST_F( LockPrimTests, Simple )
{
    CUL::LckPrim<int> value;
    value.setVal( 10 );
}