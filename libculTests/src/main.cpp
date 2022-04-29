#include "Gtest.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"

int main( int argc, char** argv )
{
    std::cout << "Begin tests.\n";

    ::testing::InitGoogleTest( &argc, argv );
    const int result = RUN_ALL_TESTS();
    return result;
}