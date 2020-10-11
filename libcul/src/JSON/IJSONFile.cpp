#include "CUL/JSON/IJSONFile.hpp"


using namespace CUL;
using namespace JSON;

IJSONFile::IJSONFile( const String& path ):
    FS::IFile( path )
{
}

IJSONFile::~IJSONFile()
{
}