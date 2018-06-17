#include "Gtest.hpp"

int main( int argc, char **argv )
{
    ::testing::InitGoogleTest( &argc, argv );
    const int result = RUN_ALL_TESTS();
#ifdef _WIN32
    int x;
    std::cout << "Press key to exit tests...";
    std::cin >> x;
    return result;
#else
    return result;
#endif
}