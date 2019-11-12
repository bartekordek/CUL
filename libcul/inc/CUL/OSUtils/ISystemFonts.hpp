#pragma once

#include "CUL/CUL.hpp"
#include "CUL/UselessMacros.hpp"
#include "CUL/Filesystem/FS.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( OSUtils )

using FontFilesPaths = FS::FileList;

class CULLib_API ISystemFonts
{
public:
    ISystemFonts() = default;
    virtual ~ISystemFonts() = default;

    virtual const FontFilesPaths& getFontFilesPaths() = 0;
    virtual void addSearchPath( const FS::Path& dir ) = 0;

protected:
private:
    ISystemFonts& operator=( const ISystemFonts& rhv ) = delete;
    ISystemFonts( const ISystemFonts& rhv ) = delete;

};

CULLib_API ISystemFonts* getUtil();

NAMESPACE_END( OSUtils )
NAMESPACE_END( CUL )