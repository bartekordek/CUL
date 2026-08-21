#include "CUL/OSUtils/Misc.hpp"
#if defined( CUL_WINDOWS )
#include <Windows.h>

namespace CUL
{
void Misc::openFileWithDefaultApp( const char* inPath, const char* inArgs )
{
    ShellExecute( nullptr,
                   "open",
                  inPath,       // file to open
                  inArgs,  // arguments passed to the app
                   nullptr,
                   SW_SHOWNORMAL );
}
void Misc::openFileWithDefaultApp( const wchar_t* inPath, const wchar_t* inArgs )
{
    ShellExecuteW( nullptr,
                  L"open",
                  inPath,  // file to open
                  inArgs,  // arguments passed to the app
                  nullptr,
                  SW_SHOWNORMAL );
    }
}  // namespace CUL

#endif / / #if !defined( CUL_WINDOWS )