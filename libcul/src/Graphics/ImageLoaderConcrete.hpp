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

    IImage* loadImage( const FS::Path& path, bool rgba = false ) override;
    IImage* loadImage(DataType* data, unsigned width, unsigned height) override;
    void deleteImage( const FS::Path& path ) override;
    IImage* findImage( const FS::Path& path ) override;

    ~ImageLoaderConcrete();

protected:

private:
    IImageLoader* getLoader( const String& fileExt );

    std::map<String, std::unique_ptr<IImageLoader>> m_loaders;

// Deleted
    ImageLoaderConcrete( const ImageLoaderConcrete& arg ) = delete;
    ImageLoaderConcrete& operator=( const ImageLoaderConcrete& rhv ) = delete;
    ImageLoaderConcrete( ImageLoaderConcrete&& arg ) = delete;
    ImageLoaderConcrete& operator=( ImageLoaderConcrete&& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )