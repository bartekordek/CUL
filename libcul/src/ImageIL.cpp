#include "ImageIL.hpp"

#if _MSC_VER
#pragma warning( push, 0 )
#pragma warning( disable: 4626 )
#pragma warning( disable: 4710 )
#endif
#include "IL/il.h"
#ifdef _MSC_VER
#pragma warning( pop )
#endif

#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL;

ImageIL::ImageIL()
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

ImageIL::~ImageIL()
{
}

ImageIL& ImageIL::operator=( const ImageIL& rhv )
{
    if( this != &rhv )
    {
        m_data = rhv.m_data;
    }
    return *this;
}

ImageIL& ImageIL::operator=( const FS::Path& path )
{
    loadImageFrom( path );
    return *this;
}

const DataType* ImageIL::getData()const
{
    return m_data;
}

const FS::Path& ImageIL::getPath()const
{
    return m_path;
}

//TODO: After implementation remove guards.
#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4100 )
#pragma warning( disable: 4189 )
#endif

void ImageIL::loadImageFrom( const FS::Path& path )
{
    Assert::simple( path.exists(), CsStr( "Path does not exist: " ) + path.getPath() );

    ILuint imgID = 0;
    ilGenImages( 1, &imgID );
    ilBindImage( imgID );
    ILboolean success = ilLoadImage( path.getPath().cStr() );
    Assert::simple( IL_TRUE == success, "Unable to load: " + path.getPath() );
    success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
    Assert::simple( IL_TRUE == success, "Unable to convert: " + path.getPath() );
    m_data = ilGetData();
    //auto size = IL_IMAGE_WIDTH * IL_IMAGE_HEIGHT;
    m_path = path;
}

#ifdef _MSC_VER
#pragma warning( pop )
#endif