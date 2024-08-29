#include "Graphics/ImageLoaderConcrete.hpp"

#include "Graphics/ImageLoaderSTB.hpp"
#include "Graphics/ImageLoaderTiny.hpp"
#include "Graphics/ImageLoaderBMP.hpp"
#include "Graphics/ImageLoaderData.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

#if defined(CUL_WINDOWS)
static String g_png{ L"png" };
static String g_bmp{ L"bmp" };
static String g_data{ L"data" };
#else // #if defined(CUL_WINDOWS)
static String g_png{ "png" };
static String g_bmp{ "bmp" };
static String g_data{ "data" };
#endif // #if defined(CUL_WINDOWS)

ImageLoaderConcrete::ImageLoaderConcrete( GUTILS::IConfigFile* config, CULInterface* culInterface ) : IImageLoader( culInterface )
{
    if( config )
    {
        const auto& bmpLoader = config->getValue( "BMP_LOADER" );
        if( bmpLoader == "TinyImageLoader" )
        {
            std::unique_ptr<TinyImageLoader> bmp( new TinyImageLoader( culInterface ) );
            m_loaders[g_bmp] = std::move( bmp );
        }
        else if( bmpLoader == "STBIImageLoader" )
        {
            std::unique_ptr<STBIImageLoader> bmp( new STBIImageLoader( culInterface ) );
            m_loaders[g_bmp] = std::move( bmp );
        }
        else
        {
            std::unique_ptr<ImageLoaderBMP> bmp( new ImageLoaderBMP( culInterface ) );
            m_loaders[g_bmp] = std::move( bmp );
        }

        const auto& pngLoader = config->getValue( "PNG_LOADER" );
        if( pngLoader == "TinyImageLoader" )
        {
            std::unique_ptr<TinyImageLoader> png( new TinyImageLoader( culInterface ) );
            m_loaders[g_png] = std::move( png );
        }
        else
        {
            std::unique_ptr<STBIImageLoader> png( new STBIImageLoader( culInterface ) );
            m_loaders[g_png] = std::move( png );
        }
    }
    else
    {
        std::unique_ptr<STBIImageLoader> png( new STBIImageLoader( culInterface ) );
        m_loaders[g_png] = std::move( png );

        std::unique_ptr<TinyImageLoader> bmp( new TinyImageLoader( culInterface ) );
        m_loaders[g_bmp] = std::move( bmp );
    }

    std::unique_ptr<ImageLoaderData> data( new ImageLoaderData( culInterface ) );
    m_loaders[g_data] = std::move( data );
}

IImage* ImageLoaderConcrete::loadImage( const FS::Path& path, bool rgba )
{
    const auto extension = path.getExtension();
    const auto loader = getLoader(extension);

    return loader->loadImage( path, rgba );
}

IImage* ImageLoaderConcrete::loadImage(DataType* data, unsigned width, unsigned height)
{
    return getLoader( g_data )->loadImage( data, width, height );
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

    const auto it = m_loaders.find( fileExt );
    if( it != m_loaders.end() )
    {
        return it->second.get();
    }

    if( ext == g_png )
    {
        return m_loaders[g_png].get();
    }
    else if( ext == g_bmp || ext == g_bmp )
    {
        return m_loaders[g_bmp].get();
    }
    else if( ext == g_data )
    {
        return m_loaders[g_data].get();
    }

    return nullptr;
}

ImageLoaderConcrete::~ImageLoaderConcrete()
{

}

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )