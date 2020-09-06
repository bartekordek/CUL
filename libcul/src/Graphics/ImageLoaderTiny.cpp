#include "Graphics/ImageLoaderTiny.hpp"
#include "Graphics/ImageConcrete.hpp"
#include "IMPORT_Tiny.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL;
using namespace Graphics;

TinyImageLoader::TinyImageLoader()
{

}

IImage* TinyImageLoader::loadImage( const Path& path, Cbool )
{
    int width = 0, height = 0;
    auto rawData = tinyimg_load( path.getPath().cStr(),
                                          &width, &height,
                                          TinyImgColorType::TINYIMG_RGB );

    const auto error =  tinyimg_get_error();
    if( TINYIMG_OK != error )
    {
        const auto errorStr =  tinyimg_get_error_str();
        CUL::Assert::simple( false, errorStr );
    }

    ImageInfo ii;
    ii.path = path;
    ii.size.width = width;
    ii.size.height = height;

    if( true )
    {
        ii.depth = 24;
        ii.pitch = 3 * width;
        ii.pixelFormat = PixelFormat::RGB24 ;
    }
    else
    {
        ii.depth = 24;
        ii.pitch = 3 * width;
        ii.pixelFormat = PixelFormat::RGBA32;
    }

    auto iimage = new ImageConcrete();
    auto data = reinterpret_cast<DataType*>( rawData );
    iimage->setData( data );
    iimage->setImageInfo( ii );

    return iimage;
}

void TinyImageLoader::deleteImage( const Path& path )
{
    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        m_fileList.erase( it );
    }
}

IImage* TinyImageLoader::findImage( const Path& path )
{
    IImage* result = nullptr;

    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        result = it->second.get();
    }

    return result;
}

TinyImageLoader::~TinyImageLoader()
{

}