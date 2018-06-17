#include "CUL/FileFactory.hpp"
#include "FileRegularImpl.hpp"
#include "CSVFile.hpp"

using namespace CUL;
using namespace FS;

IFilePtr FileFactory::createRegularFile( const Path& path )
{
    auto fr = new FileRegularImpl( path.getPath() );
    std::shared_ptr<IFile> file( fr );
    return file;
}

IFilePtr FileFactory::createCSVFile( const Path& path )
{
    auto csvFile = new CSVFile( path.getPath() );
    IFilePtr file( csvFile );
    return file;
}