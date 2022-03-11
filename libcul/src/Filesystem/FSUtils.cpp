#include "Filesystem/FSUtils.hpp"

#include "CUL/STL_IMPORTS/STD_cstdlib.hpp"
#include "CUL/STL_IMPORTS/STD_clocale.hpp"
#include "CUL/STL_IMPORTS/STD_string.hpp"
#include "CUL/STL_IMPORTS/STD_codecvt.hpp"

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
    {
        return std::string();
    }

#ifdef _MSC_VER
    UINT codePage = CP_UTF8;
    DWORD dwFlags = WC_COMPOSITECHECK;
    int size_needed = WideCharToMultiByte( codePage, dwFlags, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL );
    std::string strTo( (size_t)size_needed, 0 );
    WideCharToMultiByte( codePage, dwFlags, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL );
    return strTo;
#else
    std::string s( wstr.begin(), wstr.end() );
    return s;
    //std::wstring str = std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(wstr);
#endif
}

std::wstring CUL::FS::s2ws( const std::string& str )
{
    if( str.empty() )
    {
        return std::wstring();
    }

#ifdef _MSC_VER
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
#else
    std::string inCurLocale = setlocale(LC_ALL, "");
    const char* _Source = str.c_str();
    size_t _Dsize = mbstowcs(NULL, _Source, 0) + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    mbstowcs(_Dest,_Source,_Dsize);
    std::wstring result = _Dest;
    delete []_Dest;
    setlocale(LC_ALL, inCurLocale.c_str());
    return result;
#endif
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif