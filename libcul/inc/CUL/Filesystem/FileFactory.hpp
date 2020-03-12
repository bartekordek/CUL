#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/ICSVFile.hpp"
#include "CUL/JSON/IJSONFile.hpp"
#include "CUL/Graphics/IRawImage.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( FS )

using IFilePtr = std::shared_ptr<IFile>;
using ICSVFilePtr = std::shared_ptr<ICSVFile>;
using IJSONFilePtr = std::shared_ptr<JSON::IJSONFile>;
using IRawImagePtr = std::shared_ptr<Graphics::IRawImage>;

class CULLib_API FileFactory
{
public:
    static IFile* createRegularFileRawPtr();
    static ICSVFile* createCSVFileRawPtr();
    static JSON::IJSONFile* createJSONFileRawPtr();
    static Graphics::IRawImage* createRawImageRawPtr();

    static IFile* createFileFromPath( const Path& path );
    static IFile* createRegularFileRawPtr( const Path& path );
    static ICSVFile* createCSVFileRawPtr( const Path& path );
    static JSON::IJSONFile* createJSONFileRawPtr( const Path& path );
    static Graphics::IRawImage* createRawImageRawPtr( const Path& path );
protected:
private:
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )