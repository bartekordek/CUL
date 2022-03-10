#include "CUL/Filesystem/FS.hpp"

#include "Filesystem/FSApiFS.hpp"
#include "Filesystem/FSApiCppFS.hpp"

using namespace CUL;
using namespace FS;

FSApi* FSApi::crateInstance( const CUL::String& type, FileFactory* ff, CULInterface* culInterface )
{
    FSApi* result = nullptr;
    if( type == "FSApiFS" )
    {
        result = new FSApiFS( ff, culInterface );
    }
    else if( type == "FSApiCppFS" )
    {
        result = new FSApiCppFS(ff, culInterface);
    }
    return result;
}

FSApi::FSApi()
{
}

FSApi::~FSApi()
{
}