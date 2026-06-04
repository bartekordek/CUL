#include "MathTest.hpp"
#include "CUL/GenericUtils/SIMD.hpp"
#include "CUL/STL_IMPORTS/STD_array.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"

MathTests::MathTests()
{
}


constexpr std::size_t g_dataSize{ 1234567u };

TEST_F( MathTests, SUM_ISPC )
{
    std::vector<float> one(g_dataSize, 1.f);
    std::vector<float> two( g_dataSize, 2.f );
    std::vector<float> result( g_dataSize,0.f );

    CUL::GUTILS::sum( one.data(), two.data(), g_dataSize, result.data() );
}

TEST_F( MathTests, SUM_NORMAL )
{
    std::vector<float> one( g_dataSize, 1.f );
    std::vector<float> two( g_dataSize, 2.f );
    std::vector<float> result( g_dataSize, 0.f );

    for( std::size_t i = 0u; i < g_dataSize; ++i )
    {
        result[i] = one[i] + one[i];
    }
}
