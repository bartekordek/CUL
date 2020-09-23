#pragma once

#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class ImageLoaderConcrete final:
    public IImageLoader
{
public:
    ImageLoaderConcrete( GUTILS::IConfigFile* file );

    IImage* loadImage( const Path& path, Cbool rgba = false ) override;
    void deleteImage( const Path& path ) override;
    IImage* findImage( const Path& path ) override;

    ~ImageLoaderConcrete();

protected:

private:
    IImageLoader* getLoader( CsStr& fileExt );

    std::map<String, std::unique_ptr<IImageLoader>> m_loaders;

// Deleted
    ImageLoaderConcrete( const ImageLoaderConcrete& arg ) = delete;
    ImageLoaderConcrete& operator=( const ImageLoaderConcrete& rhv ) = delete;
    ImageLoaderConcrete( ImageLoaderConcrete&& arg ) = delete;
    ImageLoaderConcrete& operator=( ImageLoaderConcrete&& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )