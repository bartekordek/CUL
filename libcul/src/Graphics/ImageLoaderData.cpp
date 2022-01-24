#include "Graphics/ImageLoaderData.hpp"
#include "Graphics/ImageConcrete.hpp"

using namespace CUL;
using namespace Graphics;

ImageLoaderData::ImageLoaderData( CULInterface* culInterface ) : IImageLoader( culInterface )
{

}

IImage* ImageLoaderData::loadImage( DataType* data, unsigned width, unsigned height )
{
    // TODO: FIX object managing - images on every loader.
    auto result = new ImageConcrete();

    result->setData( data );
    ImageInfo ii;
    ii.size = { (int)width, (int)height };
    result->setImageInfo( ii );
    return result;
}

void ImageLoaderData::deleteImage( const FS::Path& path )
{
    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        m_fileList.erase( it );
    }
}

IImage* ImageLoaderData::findImage( const FS::Path& path )
{
    IImage* result = nullptr;

    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        result = it->second.get();
    }

    return result;
}

ImageLoaderData::~ImageLoaderData()
{

}