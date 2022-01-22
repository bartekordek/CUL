#include "Graphics/ImageLoaderConcrete.hpp"

#include "Graphics/ImageLoaderSTB.hpp"
#include "Graphics/ImageLoaderTiny.hpp"
#include "Graphics/ImageLoaderBMP.hpp"
#include "Graphics/ImageLoaderData.hpp"

using namespace CUL;
using namespace Graphics;

ImageLoaderConcrete::ImageLoaderConcrete( GUTILS::IConfigFile* config )
{
    if( config )
    {
        const auto& bmpLoader = config->getValue( "BMP_LOADER" );
        if( bmpLoader == "TinyImageLoader" )
        {
            std::unique_ptr<TinyImageLoader> bmp( new TinyImageLoader() );
            m_loaders["bmp"] = std::move( bmp );
        }
        else if( bmpLoader == "STBIImageLoader" )
        {
            std::unique_ptr<STBIImageLoader> bmp( new STBIImageLoader() );
            m_loaders["bmp"] = std::move( bmp );
        }
        else
        {
            std::unique_ptr<ImageLoaderBMP> bmp( new ImageLoaderBMP() );
            m_loaders["bmp"] = std::move( bmp );
        }

        const auto& pngLoader = config->getValue( "PNG_LOADER" );
        if( pngLoader == "TinyImageLoader" )
        {
            std::unique_ptr<TinyImageLoader> png( new TinyImageLoader() );
            m_loaders["png"] = std::move( png );
        }
        else if( pngLoader == "DevIL" )
        {
        }
        else
        {
            std::unique_ptr<STBIImageLoader> png( new STBIImageLoader() );
            m_loaders["png"] = std::move( png );
        }
    }
    else
    {
        std::unique_ptr<STBIImageLoader> png( new STBIImageLoader() );
        m_loaders["png"] = std::move( png );

        std::unique_ptr<TinyImageLoader> bmp( new TinyImageLoader() );
        m_loaders["bmp"] = std::move( bmp );
    }

    std::unique_ptr<ImageLoaderData> data( new ImageLoaderData() );
    m_loaders["data"] = std::move( data );
}

IImage* ImageLoaderConcrete::loadImage( const FS::Path& path, bool rgba )
{
    return getLoader( path.getExtension() )->loadImage( path, rgba );
}

IImage* ImageLoaderConcrete::loadImage(DataType* data, unsigned width, unsigned height)
{
    return getLoader("data")->loadImage(data, width, height);
}

void ImageLoaderConcrete::deleteImage( const FS::Path& path )
{
    return getLoader( path )->deleteImage( path );
}

IImage* ImageLoaderConcrete::findImage( const FS::Path& path )
{
    return getLoader( path )->findImage( path );
}

IImageLoader* ImageLoaderConcrete::getLoader( const String& fileExt )
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
    else if (ext == "data")
    {
        return m_loaders["data"].get();
    }
    else
    {
        return nullptr;
    }
}

ImageLoaderConcrete::~ImageLoaderConcrete()
{

}