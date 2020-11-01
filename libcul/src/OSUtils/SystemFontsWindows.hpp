#pragma once

#include "CUL/OSUtils/ISystemFonts.hpp"
#include "CUL/Filesystem/FS.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( OSUtils )

class SystemFontsWindows:
    public ISystemFonts
{
public:
    SystemFontsWindows( FS::FSApi* fsApi, LOG::ILogger* logger );

    const FontFilesPaths& getFontFilesPaths() override;
    void addSearchPath( const FS::Path& dir ) override;

    virtual ~SystemFontsWindows();
protected:
private:
    SystemFontsWindows& operator=( const SystemFontsWindows& rhv ) = delete;
    SystemFontsWindows( const SystemFontsWindows& rhv ) = delete;

    void updateFontFilesList();
    void getWindowsPath();

    FS::FSApi* m_fsApi = nullptr;
    LOG::ILogger* m_logger = nullptr;

    FontFilesPaths m_defaultDirsWithFonts;
    FontFilesPaths m_fontFilesList;
};

NAMESPACE_END( OSUtils )
NAMESPACE_END( CUL )