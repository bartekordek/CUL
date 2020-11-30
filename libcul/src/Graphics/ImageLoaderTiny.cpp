#include "Graphics/ImageLoaderTiny.hpp"
#include "Graphics/ImageConcrete.hpp"
#include "IMPORT_Tiny.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL;
using namespace Graphics;

TinyImageLoader::TinyImageLoader()
{

}

IImage* TinyImageLoader::loadImage( const FS::Path& path, Cbool )
{
    int width = 0, height = 0;
    auto type = TinyImgColorType::TINYIMG_RGB;
    DataType* rawData = tinyimg_load(
        path.getPath().cStr(),
        &width, &height,
        type );

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
    ii.depth = 24;
    ii.pitch = 4 * width;
    ii.pixelFormat = PixelFormat::TEST;

    //if( type == TinyImgColorType::TINYIMG_RGB )
    //{
    //    ii.depth = 24;
    //    ii.pitch = 4 * width;
    //    ii.pixelFormat = PixelFormat::RGB24;
    //}
    //else
    //{
    //    ii.depth = 24;
    //    ii.pitch = 4 * width;
    //    ii.pixelFormat = PixelFormat::RGBA32;
    //}

    auto iimage = new ImageConcrete();
    iimage->setData( rawData );
    iimage->setImageInfo( ii );

    return iimage;
}

void TinyImageLoader::deleteImage( const FS::Path& path )
{
    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        m_fileList.erase( it );
    }
}

IImage* TinyImageLoader::findImage( const FS::Path& path )
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