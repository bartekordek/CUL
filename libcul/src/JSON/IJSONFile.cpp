#include "CUL/JSON/IJSONFile.hpp"


using namespace CUL;
using namespace JSON;

IJSONFile::IJSONFile( CsStr& path ):
    FS::IFile( path )
{
}

IJSONFile::~IJSONFile()
{
}