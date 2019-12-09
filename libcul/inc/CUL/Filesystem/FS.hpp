#pragma once

#include "CUL/Filesystem/Path.hpp"
#include "CUL/String.hpp"
#include "CUL/UselessMacros.hpp"
#include "CUL/STL_IMPORTS/STD_set.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

using FileList = std::set<Path>;

class CULLib_API FSApi
{
public:
    FSApi();
    virtual ~FSApi();
    static String getCurrentDir();
    static const FileList getFilesUnderDirectory( const Path& directory );
protected:
private:
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )