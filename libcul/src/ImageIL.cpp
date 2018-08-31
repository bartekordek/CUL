#include "ImageIL.hpp"

#if _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 4626 )
#endif
#include "IL/il.h"
#ifdef _MSC_VER
#pragma warning( pop )
#endif

#include "CUL/SimpleAssert.hpp"

using namespace CUL;

ImageIL::ImageIL( void )
{
}

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4100 )
#endif
ImageIL::ImageIL( const ImageIL& val )
{
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

ImageIL::~ImageIL( void )
{
}

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4100 )
#endif
ImageIL& ImageIL::operator=( const ImageIL& rhv )
{
    return *this;
}
#ifdef _MSC_VER
#pragma warning( pop )
#endif

ImageIL& ImageIL::operator=( const FS::Path& path )
{
    loadImageFrom( path );
    return *this;
}

//TODO: After implementation remove guards.
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4100 )
#pragma warning( disable: 4189 )
#endif
void ImageIL::loadImageFrom( const FS::Path& path )
{
    Assert::simple( path.exists(), "Path does not exist: " + path.getPath() );

    ILuint imgID = 0;
    ilGenImages( 1, &imgID );
    ilBindImage( imgID );
    ILboolean success = ilLoadImage( path.getPath().c_str() );
    Assert::simple( success, "Unable to load: " + path.getPath() );
    success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
    Assert::simple( success, "Unable to convert: " + path.getPath() );
    this->m_data = ilGetData();
    //auto size = IL_IMAGE_WIDTH * IL_IMAGE_HEIGHT;

}
#ifdef _MSC_VER
#pragma warning( pop )
#endif
