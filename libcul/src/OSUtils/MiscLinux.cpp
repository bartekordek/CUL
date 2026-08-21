#include "CUL/OSUtils/Misc.hpp"

#if !defined( CUL_WINDOWS )

namespace CUL
{
void Misc::openFileWithDefaultApp( const char* inPath )
{
}
void Misc::openFileWithDefaultApp( const wchar_t* inPath )
{
}
}  // namespace CUL

#endif / / #if !defined( CUL_WINDOWS )