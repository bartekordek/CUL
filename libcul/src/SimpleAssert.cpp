#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

#include "boost/assert.hpp"

using namespace CUL;

void Assert::simple( const bool val, CnstMyStr& msg )
{
    if( 0 == val )
    {
        std::cerr << msg.string() << "\n";
        BOOST_ASSERT_MSG( val, msg.cStr() );
    }
}