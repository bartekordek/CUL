#pragma once

#include "CUL/CUL.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"
#include "CUL/Filesystem/Path.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( GUTILS )

class CULLib_API IConfigFile
{
public:
    IConfigFile() = default;

    static IConfigFile* createFile( const FS::Path& path );

    virtual const String& getValue( const String& valueFieldName ) const = 0;

    virtual ~IConfigFile() = default;

protected:
private:

    // Deleted:
    IConfigFile( const IConfigFile& val ) = delete;
    IConfigFile( IConfigFile&& val ) = delete;
    IConfigFile& operator=( const IConfigFile& rhv ) = delete;
    IConfigFile& operator=( IConfigFile&& rhv ) = delete;
};

NAMESPACE_END( GUTILS )
NAMESPACE_END( CUL )