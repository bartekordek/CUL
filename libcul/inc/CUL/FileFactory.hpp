#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/IFile.hpp"
#include "CUL/ICSVFile.hpp"
#include "CUL/JSON/IJSONFile.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

using IFilePtr = std::shared_ptr<IFile>;
using ICSVFilePtr = std::shared_ptr<ICSVFile>;
using IJSONFilePtr = std::shared_ptr<JSON::IJSONFile>;

class CULLib_API FileFactory
{
public:
    static IFile* createRegularFileRawPtr();
    static ICSVFile* createCSVFileRawPtr();
    static JSON::IJSONFile* createJSONFileRawPtr();

    static IFile* createRegularFileRawPtr( const Path& path );
    static ICSVFile* createCSVFileRawPtr( const Path& path );
    static JSON::IJSONFile* createJSONFileRawPtr( const Path& path );
protected:
private:
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )
