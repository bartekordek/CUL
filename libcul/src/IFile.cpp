#include "CUL/IFile.hpp"
#include "FileRegularImpl.hpp"
#include "CSVFile.hpp"
#include <iostream>

using namespace CUL;
using namespace FS;

IFile::IFile()
{
}

IFile::IFile( const std::string& fPath )
{
    std::cout << " IFile::IFile( const std::string& fPath ), fPath = " << fPath << "\n";
}

IFile::~IFile()
{
}

std::shared_ptr<IFile> IFile::createRegularFile( const Path& path )
{
    auto fr = new FileRegularImpl( path.getPath() );
    std::shared_ptr<IFile> file( fr );
    return file;
}

std::shared_ptr<IFile> IFile::createCSVFile( const Path& path )
{
    auto csvFile = new CSVFile( path.getPath() );
    std::shared_ptr<IFile> file( csvFile );
    return file;
}