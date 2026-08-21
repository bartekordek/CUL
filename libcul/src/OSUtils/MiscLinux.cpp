#include "CUL/OSUtils/Misc.hpp"

#if !defined( CUL_WINDOWS )

namespace CUL
{
void Misc::openFileWithDefaultApp( const char* inPath, const char* inArgs )
{
}
void Misc::openFileWithDefaultApp( const wchar_t* inPath, const wchar_t* inArgs )
{
}
}  // namespace CUL

#endif  // #if !defined( CUL_WINDOWS )