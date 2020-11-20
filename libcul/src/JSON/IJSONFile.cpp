#include "CUL/JSON/IJSONFile.hpp"


using namespace CUL;
using namespace JSON;

IJSONFile::IJSONFile( const String& path, CULInterface* interface ):
    FS::IFile( path, interface )
{
}

IJSONFile::~IJSONFile()
{
}