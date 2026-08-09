#pragma once

#include "CUL/UselessMacros.hpp"
#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Filesystem/Directory.hpp"
#include "CUL/ICSVFile.hpp"
#include "CUL/JSON/JSONFile.hpp"
#include "CUL/Graphics/IImage.hpp"

NAMESPACE_BEGIN( CUL )
class CULInterface;
NAMESPACE_BEGIN( FS )

using IFilePtr = std::shared_ptr<IFile>;
using ICSVFilePtr = std::shared_ptr<ICSVFile>;
using JSONFilePtr = std::shared_ptr<JSON::JSONFile>;
using IRawImagePtr = std::shared_ptr<Graphics::IImage>;

class CULLib_API FileFactory final
{
public:
    FileFactory( CULInterface* culInterface );

    Graphics::IImage* createRawImageRawPtr();

    IFile* createFileFromPath( const Path& path );
    IFile* createRegularFileRawPtr( const Path& path );
    ICSVFile* createCSVFileRawPtr( const Path& path );
    JSONFilePtr createJSONFileRawPtr( const Path& path );
    Graphics::IImage* createRawImageRawPtr( const Path& path );
protected:
private:
    CULInterface* m_culInterface = nullptr;

// Deleted:
    FileFactory( const FileFactory& arg ) = delete;
    FileFactory( FileFactory&& arg ) = delete;
    FileFactory& operator=( const FileFactory& arg ) = delete;
    FileFactory& operator=( FileFactory&& arg ) = delete;
};

NAMESPACE_END( FS )
NAMESPACE_END( CUL )