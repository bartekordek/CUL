#include "Graphics/ImageLoaderConcrete.hpp"

#include "Graphics/ImageLoaderSTB.hpp"
#include "Graphics/ImageLoaderTiny.hpp"
#include "Graphics/ImageLoaderDevil.hpp"

using namespace CUL;
using namespace Graphics;

ImageLoaderConcrete::ImageLoaderConcrete()
{
    std::unique_ptr<DevilImageLoader> png( new DevilImageLoader() );
    //std::unique_ptr<STBIImageLoader> png( new STBIImageLoader() );
    m_loaders["png"] = std::move( png );

    //std::unique_ptr<TinyImageLoader> bmp( new TinyImageLoader() );
    std::unique_ptr<DevilImageLoader> bmp( new DevilImageLoader() );
    m_loaders["bmp"] = std::move( bmp );

    //result = new STBIImageLoader();
    //result = new TinyImageLoader();
    //result = new DevilImageLoader();
}


IImage* ImageLoaderConcrete::loadImage( const Path& path, Cbool rgba )
{
    return getLoader( path.getExtension() )->loadImage( path, rgba );
}

void ImageLoaderConcrete::deleteImage( const Path& path )
{
    return getLoader( path )->deleteImage( path );
}

IImage* ImageLoaderConcrete::findImage( const Path& path )
{
    return getLoader( path )->findImage( path );
}

IImageLoader* ImageLoaderConcrete::getLoader( CsStr& fileExt )
{
    auto ext = fileExt;
    ext.toLower();

    if( ext == ".png" || ext == "png" )
    {
        return m_loaders["png"].get();
    }
    else if( ext == ".bmp" || ext == "bmp" )
    {
        return m_loaders["bmp"].get();
    }
    else
    {
        return nullptr;
    }
}

ImageLoaderConcrete::~ImageLoaderConcrete()
{

}