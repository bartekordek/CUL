#include "LockPrimTests.hpp"
#include "CUL/GenericUtils/LckPrim.hpp"

TEST_F( LockPrimTests, Simple )
{
    CUL::GUTILS::LckPrim<int> value;
    value.setVal( 10 );
}