#include "Benchmark.hpp"

#include "CUL/Math/Angle.hpp"

using namespace CUL;
using namespace MATH;

constexpr std::size_t g_vecSize = 16777216;
std::vector<std::int32_t> vec0;
std::vector<std::int32_t> vec1;
std::vector<std::int32_t> vec2;

std::int32_t dummyCalc( std::int32_t index )
{
    std::int32_t result = index;
    result = result * index;
    return result;
}

void Benchmark::SetUpTestCase()
{
    vec0.resize( g_vecSize );
    vec1.resize( g_vecSize );
    vec2.resize( g_vecSize );

    for( std::size_t i = 0; i < g_vecSize; ++i )
    {
        vec0[i] = (std::int32_t)i;
        vec1[i] = (std::int32_t)i;
        vec2[i] = (std::int32_t)i;
    }
}

void Benchmark::SetUp()
{

}

Benchmark::Benchmark()
{

}

TEST_F( Benchmark, test0 )
{
    for( auto& val: vec0 )
    {
        val = dummyCalc( val );
    }
}

TEST_F( Benchmark, test1 )
{
    for( const auto& val : vec1 )
    {
        dummyCalc( val );
    }
}

TEST_F( Benchmark, test2 )
{
    for( std::size_t i = 0; i < g_vecSize; ++i )
    {
        vec2[i] = dummyCalc( vec2[i] );
    }
}

void Benchmark::TearDownTestCase()
{
    vec0.resize( 0u );
    vec1.resize( 0u );
    vec2.resize( 0u );
}