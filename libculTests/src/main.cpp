#include "Gtest.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"

int main( int argc, char** argv )
{
    //std::setlocale( LC_CTYPE, nullptr );         // for C and C++ where synced with stdio
    //std::locale::global( std::locale( "" ) );  // for C++

    std::setlocale( LC_CTYPE, "en_US.UTF-8" );
    std::locale::global( std::locale( std::setlocale( LC_ALL, nullptr ) ) );

    ::testing::InitGoogleTest( &argc, argv );
    const int result = RUN_ALL_TESTS();
    return result;
}