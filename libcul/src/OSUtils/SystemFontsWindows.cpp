#if _WIN32
#include "OSUtils/SystemFontsWindows.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "GUARD_windows.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"
#include "CUL/Windows/INCLUDE_dwrite.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/Log/ILogContainer.hpp"

using namespace CUL;
using SystemFontsWindows = OSUtils::SystemFontsWindows;
using FontFilesPaths = OSUtils::FontFilesPaths;

SystemFontsWindows::SystemFontsWindows()
{
    updateFontFilesList();
}

const FontFilesPaths& SystemFontsWindows::getFontFilesPaths()
{
    return m_fontFilesList;
}

void SystemFontsWindows::addSearchPath( const FS::Path& dir )
{
    m_defaultDirsWithFonts.insert( dir );
}

void SystemFontsWindows::updateFontFilesList()
{
    getWindowsPath();
    for( const auto& dir : m_defaultDirsWithFonts )
    {
        const auto directory = FS::FSApi::getDirectory( dir );
        const auto files = directory->getChildList();
        for( const auto& file : files )
        {
            const FS::Path& path = file->getPath();
            if( path.getExtension() == ".ttf" )
            {
                m_fontFilesList.insert( path );
            }
        }
        delete directory;
    }
}

CHOOSEFONT ShowSelectFont()
{
    HWND hwnd = GetForegroundWindow();
    CHOOSEFONT cf = { sizeof( CHOOSEFONT ) };
    LOGFONT* lf = new LOGFONT;
    HDC hdc = GetDC( hwnd );

    HFONT hlf = (HFONT) GetCurrentObject( hdc, OBJ_FONT );
    GetObject( hlf, sizeof( LOGFONT ), lf );
    cf.Flags = CF_EFFECTS | CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
    cf.hwndOwner = hwnd;
    cf.lpLogFont = lf;
    cf.rgbColors = GetTextColor( hdc );
    ChooseFont( &cf );
    ReleaseDC( hwnd, hdc );
    cf.lpLogFont = lf;
    return cf;
}

#ifdef _MSC_VER
// Yes, I know that is a Spectre mitigation.
// But for now, I let this as TODO, since i don't know
// How to fix this.
// TODO
#pragma warning( push )
#pragma warning( disable: 5045 )
#endif

bool GetFontData1( const HFONT fontHandle, std::vector<char>& data )
{
    bool result = false;
    HDC hdc = ::CreateCompatibleDC( NULL );
    if( hdc != NULL )
    {
        ::SelectObject( hdc, fontHandle );
        const size_t size = ::GetFontData( hdc, 0, 0, NULL, 0 );
        if( size > 0 )
        {
            char* buffer = new char[size];
            if( ::GetFontData(
                hdc,
                0,
                0,
                buffer,
                static_cast<DWORD>( size ) ) == static_cast<DWORD>( size ) )
            {
                data.resize( size );
                memcpy( &data[0], buffer, size );
                result = true;
            }
            delete[] buffer;

        }
        ::DeleteDC( hdc );
    }
    return result;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif

#pragma warning( push, 0 )
#pragma warning( disable: 4700 )
void SystemFontsWindows::getWindowsPath()
{
    TCHAR windir[MAX_PATH];
    GetWindowsDirectory( windir, MAX_PATH );
    auto g_hfFont = GetStockObject( DEFAULT_GUI_FONT );
    CHOOSEFONT cf = { sizeof( CHOOSEFONT ) };
    LOGFONT lf;
    COLORREF g_rgbText = RGB( 0, 0, 0 );
    GetObject( g_hfFont, sizeof( LOGFONT ), &lf );
    cf.Flags = CF_EFFECTS | CF_INITTOLOGFONTSTRUCT | CF_SCREENFONTS;
    cf.lpLogFont = &lf;
    cf.rgbColors = g_rgbText;
    HFONT hf = CreateFontIndirect( &lf );
    LOGFONT logFont;
    ::ZeroMemory( &logFont, sizeof( logFont ) );
    LOGFONT LogFont;
    ZeroMemory( &LogFont, sizeof( LogFont ) );

    auto defaultGuiFontStockObject = GetStockObject( DEFAULT_GUI_FONT );
    auto defaultFontName = static_cast<HFONT>(defaultGuiFontStockObject);
    std::vector<char> data;
    GetFontData1( defaultFontName, data );

    DWORD table;
    DWORD offset;
    PVOID buffer;
    DWORD cjBuffer = 0;
    

    CUL::LOG::LOG_CONTAINER::getLogger()->log( "DEFAULT FONT NAME: " + CUL::String( hf ) );
    CUL::LOG::LOG_CONTAINER::getLogger()->log( "DEFAULT FONT NAME: " + CUL::String( defaultFontName ) );

    FS::Path windowsPath( windir );
    FS::Path windowsFonts = windowsPath + "/Fonts";
    m_defaultDirsWithFonts.insert( windowsFonts );
}


SystemFontsWindows::~SystemFontsWindows()
{
}

#pragma warning( pop )
#endif