#pragma once

#include "CUL/Log/ILogger.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( OSUtils )

using FontFilesPaths = std::set<FS::Path>;

class CULLib_API ISystemFonts
{
public:
    static ISystemFonts* createConcrete( CUL::FS::FSApi* fsApis, LOG::ILogger* logger );

    ISystemFonts() = default;

    virtual const FontFilesPaths& getFontFilesPaths() = 0;
    virtual void addSearchPath( const FS::Path& dir ) = 0;

    virtual ~ISystemFonts() = default;
protected:
private:
    ISystemFonts( const ISystemFonts& rhv ) = delete;
    ISystemFonts( ISystemFonts&& rhv ) = delete;
    ISystemFonts& operator=( const ISystemFonts& rhv ) = delete;
    ISystemFonts& operator=( ISystemFonts&& rhv ) = delete;
};

NAMESPACE_END( OSUtils )
NAMESPACE_END( CUL )