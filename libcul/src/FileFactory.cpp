#include "CUL/FileFactory.hpp"
#include "FileRegularImpl.hpp"
#include "CSVFile.hpp"
#include "JSON/JSONFileConcrete.hpp"

using namespace CUL;
using namespace FS;

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

JSON::IJSONFile* FileFactory::createJSONFile( const Path& path )
{
    auto result = createJSONFile();
    result->changePath( path );
    return result;
}

JSON::IJSONFile* FileFactory::createJSONFile()
{
    return new JSON::JSONFileConcrete();
}