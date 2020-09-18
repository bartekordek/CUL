#pragma once

#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class ImageLoaderBMP final:
    public IImageLoader
{
public:
    ImageLoaderBMP();

    IImage* loadImage( const Path& path, Cbool rgba = false ) override;
    IImage* loadImage2( const Path& path, Cbool rgba = false ) ;
    void printFileSize( const CUL::Graphics::Path& path );
    void deleteImage( const Path& path ) override;
    IImage* findImage( const Path& path ) override;

    ~ImageLoaderBMP();

protected:

private:
    using FileList = std::map<String, std::unique_ptr<IImage>>;
    FileList m_fileList;

private: // Deleted
    ImageLoaderBMP( const ImageLoaderBMP& arg ) = delete;
    ImageLoaderBMP( ImageLoaderBMP&& arg ) = delete;
    ImageLoaderBMP& operator=( const ImageLoaderBMP& rhv ) = delete;
    ImageLoaderBMP& operator=( ImageLoaderBMP&& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )