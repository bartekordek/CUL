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

std::string CUL::FS::ws2s( const std::wstring& wstr )
{
    if( wstr.empty() )
        return std::string();
    UINT codePage = CP_UTF8;
    DWORD dwFlags = WC_COMPOSITECHECK;
    int size_needed = WideCharToMultiByte( codePage, dwFlags, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL );
    std::string strTo( (size_t)size_needed, 0 );
    WideCharToMultiByte( codePage, dwFlags, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL );
    return strTo;
}

std::wstring CUL::FS::s2ws( const std::string& str )
{
    if( str.empty() )
    {
        return std::wstring();
    }

    std::wstring result;
    UINT codePage = CP_UTF8;
    DWORD dwFlags = 0;
    int cbMultiByte = -1;
    int wchars_num = MultiByteToWideChar( codePage, dwFlags, str.c_str(), cbMultiByte, NULL, 0 );
    wchar_t* wstr = new wchar_t[static_cast<size_t>(wchars_num)];
    MultiByteToWideChar( codePage, dwFlags, str.c_str(), cbMultiByte, wstr, wchars_num );
    result = wstr;
    delete[] wstr;
    return result;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif