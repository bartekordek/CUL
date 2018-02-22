#include "CUL/SimpleAssert.hpp"
#include "boost/assert.hpp"

using namespace CUL;

void Assert::simple( const bool val, const char* msg )
{
    if( msg )
    {
        BOOST_ASSERT_MSG( val, msg );
    }
    else
    {
        BOOST_ASSERT( val );
    }
}