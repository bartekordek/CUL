#pragma once

#include "CUL/OSUtils/ISystemFonts.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( OSUtils )

class SystemFontsWindows:
    public ISystemFonts
{
public:
    SystemFontsWindows();
    virtual ~SystemFontsWindows();

    const FontFilesPaths& getFontFilesPaths() override;
    void addSearchPath( const FS::Path& dir ) override;

protected:
private:
    SystemFontsWindows& operator=( const SystemFontsWindows& rhv ) = delete;
    SystemFontsWindows( const SystemFontsWindows& rhv ) = delete;

    void updateFontFilesList();
    void getWindowsPath();

    FontFilesPaths m_defaultDirsWithFonts;
    FontFilesPaths m_fontFilesList;

};

NAMESPACE_END( OSUtils )
NAMESPACE_END( CUL )