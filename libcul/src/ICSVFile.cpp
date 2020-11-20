#include "CUL/ICSVFile.hpp"

using namespace CUL::FS;

ICSVFile::ICSVFile( const String& path, CULInterface* interface ):
    IFile( path, interface )
{
}

ICSVFile::~ICSVFile()
{
}