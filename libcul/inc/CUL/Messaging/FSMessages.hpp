#pragma once

#include <CUL/String/StringWrapper.hpp>
#include <CUL/STL_IMPORTS/STD_variant.hpp>

namespace CUL
{

struct CULLib_API SBigMD5FileCalc
{
    std::variant<float, bool> Progress;
    float percentage = 0.f;
    StringWr Path;
};

}