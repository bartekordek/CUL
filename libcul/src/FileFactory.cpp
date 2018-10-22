#include "CUL/FileFactory.hpp"
#include "FileRegularImpl.hpp"
#include "CSVFile.hpp"
#include "JSON/JSONFileConcrete.hpp"

using IFile = CUL::FS::IFile;
using Path = CUL::FS::Path;
using FileFactory = CUL::FS::FileFactory;
using ICSVFile = CUL::FS::ICSVFile;
using IJSONFile = CUL::JSON::IJSONFile;

IFile* FileFactory::createRegularFile( const Path& path )
{
    auto file = createRegularFile();
    file->changePath( path );
    return file;
}

IFile* FileFactory::createRegularFile()
{
    return  new FileRegularImpl();
}

ICSVFile* FileFactory::createCSVFile( const Path& path )
{
    auto csvFile = createCSVFile();
    csvFile->changePath( path );
    return csvFile;
}

ICSVFile* FileFactory::createCSVFile()
{
    return new CSVFile();
}

IJSONFile* FileFactory::createJSONFile( const Path& path )
{
    auto result = createJSONFile();
    result->changePath( path );
    return result;
}

IJSONFile* FileFactory::createJSONFile()
{
    return new JSON::JSONFileConcrete();
}