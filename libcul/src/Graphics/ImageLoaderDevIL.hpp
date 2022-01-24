#pragma once

#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class ImageLoaderDevil final: public IImageLoader
{
public:
    ImageLoaderDevil( CULInterface* culInterface );

    IImage* loadImage( const FS::Path& path, bool rgba = false ) override;
    void deleteImage( const FS::Path& path ) override;
    IImage* findImage( const FS::Path& path ) override;

    ~ImageLoaderDevil();

protected:
private:
    unsigned powerOfTwo( unsigned num );
    void loadTextureFromPixels32( unsigned* pixels, unsigned imgWidth, unsigned imgHeight, unsigned texWidth, unsigned texHeight );

    using FileList = std::map<String, std::unique_ptr<IImage>>;
    FileList m_fileList;

private:  // Deleted
    ImageLoaderDevil( const ImageLoaderDevil& arg ) = delete;
    ImageLoaderDevil( ImageLoaderDevil&& arg ) = delete;
    ImageLoaderDevil& operator=( const ImageLoaderDevil& rhv ) = delete;
    ImageLoaderDevil& operator=( ImageLoaderDevil&& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )