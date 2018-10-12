#include "CUL/SimpleAssert.hpp"
#include "CUL/STD_iostream.hpp"

#include "boost/assert.hpp"

using namespace CUL;

void Assert::simple( const bool val, const std::string& msg )
{
    if( 0 == val )
    {
        std::cerr << msg << "\n";
        BOOST_ASSERT_MSG( val, msg.c_str() );
    }
}