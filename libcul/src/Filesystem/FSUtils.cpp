#include "Filesystem/FSUtils.hpp"

#include "CUL/STL_IMPORTS/STD_cstdlib.hpp"
#include "CUL/STL_IMPORTS/STD_clocale.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL::FS;


// Disabled _CRT_SECURE_NO_WARNINGS
// NOTE: TODO: find a better solution.
#ifdef _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4996 )
#endif

CUL::String CUL::FS::ws2s( const std::wstring& input )
{
    String result;
    auto outputSize = input.length() + 1;
    auto outputString = new char[outputSize];

    wcstombs( outputString, input.c_str(), outputSize );

    result = outputString;
    return result;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif