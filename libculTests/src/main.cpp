#include "Gtest.hpp"
#include <CUL/String.hpp>
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

int main( int argc, char** argv )
{
    //std::setlocale( LC_CTYPE, nullptr );         // for C and C++ where synced with stdio
    //std::locale::global( std::locale( "" ) );  // for C++

    //std::setlocale( LC_ALL, "en_US.UTF-8" );

    std::u32string tmp( U"ии" );
    CUL::String t0( L"ии" );

    const char* currentLocale = std::setlocale( LC_ALL, nullptr );
    const std::locale localeObj = std::locale( currentLocale );
    std::locale::global( localeObj );

    std::u32string tmp1( U"ии" );
    CUL::String t1( L"ии" );

    ::testing::InitGoogleTest( &argc, argv );
    const int result = RUN_ALL_TESTS();
    return result;
}