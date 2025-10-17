#include "CUL/JSON/IJSONFile.hpp"

using namespace CUL;
using namespace JSON;

IJSONFile::IJSONFile( const String& path, CULInterface* inInterface ) : FS::IFile( path, inInterface )
{
}

IJSONFile::~IJSONFile()
{
}