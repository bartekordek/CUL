#pragma once

#include "CUL/String/StringWrapper.hpp"

namespace CUL
{
class CULLib_API Misc
{
public:
    static void openFileWithDefaultApp( const char* inPath, const char* inArgs );
    static void openFileWithDefaultApp( const wchar_t* inPath, const wchar_t* inArgs );

protected:
private:
};
}  // namespace CUL