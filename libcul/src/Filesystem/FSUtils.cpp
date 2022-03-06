#include "Filesystem/FSUtils.hpp"

#include "CUL/STL_IMPORTS/STD_cstdlib.hpp"
#include "CUL/STL_IMPORTS/STD_clocale.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL::FS;

// Disabled _CRT_SECURE_NO_WARNINGS
// NOTE: TODO: find a better solution.
#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 4996 )
#pragma warning( disable : 5045 )
#endif

#ifdef CUL_WINDOWS
#include "CUL/IMPORT_stringapiset.hpp"
#endif


CUL::String CUL::FS::ws2s( const std::wstring& wstr )
{
    if( wstr.empty() )
        return std::string();
    int size_needed = WideCharToMultiByte( CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL );
    std::string strTo( (size_t)size_needed, 0 );
    WideCharToMultiByte( CP_ACP, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL );
    return strTo;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif