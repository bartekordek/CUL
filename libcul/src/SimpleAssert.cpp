#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

#include "IMPORT_boost_assert.hpp"

using namespace CUL;

void Assert::simple( Cbool val, CsStr& msg )
{
    if( 0 == val )
    {
        std::cerr << msg.string() << "\n";
        BOOST_ASSERT_MSG( val, msg.cStr() );
    }
}