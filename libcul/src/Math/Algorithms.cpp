#include "CUL/Math/Algorithms.hpp"

using namespace CUL;
using namespace MATH;
using namespace ALG;

std::vector<unsigned> fibonacciLinear( unsigned n )
{
    std::vector<unsigned> result;
    result.reserve( n );
    unsigned x = 0;
    unsigned y = 1;
    unsigned z = 0;

    do
    {
        result.push_back( x );
        z = x + y;
        x = y;
        y = z;
    }
    while( result.size() < n - 1 );


    return result;
}