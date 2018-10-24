#pragma once
#include "IFile.hpp"

#include "CUL/ICSVFile.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

using IFilePtr = std::shared_ptr<IFile>;
using ICSVFilePtr = std::shared_ptr<ICSVFile>;
class CULLib_API FileFactory
{
public:
    static IFilePtr createRegularFile( const Path& path );
    static ICSVFilePtr createCSVFile( const Path& path );
protected:
private:
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )