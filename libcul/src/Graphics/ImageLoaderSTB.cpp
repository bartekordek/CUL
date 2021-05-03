#include "Graphics/ImageLoaderSTB.hpp"
#include "Graphics/ImageConcrete.hpp"
#include "IMPORT_Stb.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL;
using namespace Graphics;

STBIImageLoader::STBIImageLoader()
{

}

IImage* STBIImageLoader::loadImage( const FS::Path& path, bool )
{
    int req_format = STBI_rgb_alpha;
    int width = 0, height = 0, orig_format = 0;

    stbi_uc* rawData = stbi_load( path.getPath().cStr(), &width, &height, &orig_format, req_format );

    CUL::Assert::simple( rawData != nullptr, "cannot export data." );
    auto data = reinterpret_cast<DataType*>( rawData );

    ImageInfo ii;
    ii.path = path;
    ii.size.width = width;
    ii.size.height = height;

    if( req_format == STBI_rgb )
    {
        ii.depth = 24;
        ii.pitch = 3 * width;
        ii.pixelFormat = PixelFormat::ARGB;
    }
    else
    {
        ii.depth = 24;
        ii.pitch = 4 * width;
        ii.pixelFormat = PixelFormat::RGBA;
    }

    auto iimage = new ImageConcrete();
    iimage->setData( data );
    iimage->setImageInfo( ii );

    return iimage;
}

void STBIImageLoader::deleteImage( const FS::Path& path )
{
    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        m_fileList.erase( it );
    }
}

IImage* STBIImageLoader::findImage( const FS::Path& path )
{
    IImage* result = nullptr;

    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        result = it->second.get();
    }

    return result;
}

STBIImageLoader::~STBIImageLoader()
{

}