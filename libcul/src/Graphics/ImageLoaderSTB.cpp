#include "Graphics/ImageLoaderSTB.hpp"
#include "Graphics/ImageConcrete.hpp"
#include "IMPORT_Stb.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL;
using namespace Graphics;

STBIImageLoader::STBIImageLoader()
{

}

IImage* STBIImageLoader::loadImage( const Path& path, Cbool )
{
    int req_format = STBI_rgb_alpha;
    int width, height, orig_format;

    stbi_uc* rawData = nullptr;
    if( path.getExtension() == ".bmp" || path.getExtension() == ".BMP" )
    {
        rawData = stbi_load( path.getPath().cStr(), &width, &height, &orig_format, req_format );
    }
    else
    {
        rawData = stbi_load( path.getPath().cStr(), &width, &height, &orig_format, req_format );
    }

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
        ii.pixelFormat = PixelFormat::RGB24;
    }
    else
    {
        ii.depth = 24;
        ii.pitch = 4 * width;
        ii.pixelFormat = PixelFormat::RGBA32;
    }

    auto iimage = new ImageConcrete();
    iimage->setData( data );
    iimage->setImageInfo( ii );

    return iimage;
}

void STBIImageLoader::deleteImage( const Path& path )
{
    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        m_fileList.erase( it );
    }
}

IImage* STBIImageLoader::findImage( const Path& path )
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