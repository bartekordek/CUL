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
    } while( result.size() < n - 1 );

    return result;
}

unsigned nearestPowerOfTwo( unsigned num )
{
    if( num != 0 )
    {
        --num;
        num |= ( num >> 1 );   // Or first 2 bits
        num |= ( num >> 2 );   // Or next 2 bits
        num |= ( num >> 4 );   // Or next 4 bits
        num |= ( num >> 8 );   // Or next 8 bits
        num |= ( num >> 16 );  // Or next 16 bits
        ++num;
    }
    return num;
}