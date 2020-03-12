#pragma once

#include "CUL/CUL.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( OSUtils )

using FontFilesPaths = std::set<FS::Path>;

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