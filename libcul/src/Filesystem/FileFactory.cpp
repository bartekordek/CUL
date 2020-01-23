#include "CUL/Filesystem/FileFactory.hpp"
#include "FileRegularImpl.hpp"
#include "CSVFile.hpp"
#include "JSON/JSONFileConcrete.hpp"
#include "Graphics/RawImageConcrete.hpp"

using IFile = CUL::FS::IFile;
using Path = CUL::FS::Path;
using FileFactory = CUL::FS::FileFactory;
using ICSVFile = CUL::FS::ICSVFile;
using IJSONFile = CUL::JSON::IJSONFile;

IFile* FileFactory::createRegularFileRawPtr( const Path& path )
{
    auto file = createRegularFileRawPtr();
    file->changePath( path );
    return file;
}

IFile* FileFactory::createRegularFileRawPtr()
{
    return new FileRegularImpl();
}

ICSVFile* FileFactory::createCSVFileRawPtr( const Path& path )
{
    auto csvFile = createCSVFileRawPtr();
    csvFile->changePath( path );
    return csvFile;
}

ICSVFile* FileFactory::createCSVFileRawPtr()
{
    return new CSVFile();
}

IJSONFile* FileFactory::createJSONFileRawPtr( const Path& path )
{
    auto result = createJSONFileRawPtr();
    result->changePath( path );
    return result;
}

CUL::Graphics::IRawImage* FileFactory::createRawImageRawPtr( const Path& path )
{
    auto rawConcrete = static_cast<Graphics::RawImageConcrete*>( createRawImageRawPtr() );
    rawConcrete->loadFromFile( path.getPath() );
    return rawConcrete;
}

IJSONFile* FileFactory::createJSONFileRawPtr()
{
    return new JSON::JSONFileConcrete();
}

CUL::Graphics::IRawImage* FileFactory::createRawImageRawPtr()
{
    return new Graphics::RawImageConcrete();
}