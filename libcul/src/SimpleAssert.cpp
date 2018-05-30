#include "CUL/SimpleAssert.hpp"
#include "boost/assert.hpp"

using namespace CUL;

void Assert::simple( const bool val, const std::string& msg )
{
    BOOST_ASSERT_MSG( val, msg.c_str() );
}