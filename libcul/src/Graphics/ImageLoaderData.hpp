#pragma once

#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class ImageLoaderData final:
    public IImageLoader
{
public:
    ImageLoaderData( CULInterface* culInterface );

    IImage* loadImage( DataType* data, unsigned width, unsigned height ) override;
    void deleteImage( const FS::Path& path ) override;
    IImage* findImage( const FS::Path& path ) override;

    ~ImageLoaderData();

protected:

private:
    using FileList = std::map<std::string, std::unique_ptr<IImage>>;
    FileList m_fileList;

private: // Deleted
    ImageLoaderData( const ImageLoaderData& arg ) = delete;
    ImageLoaderData( ImageLoaderData&& arg ) = delete;
    ImageLoaderData& operator=( const ImageLoaderData& rhv ) = delete;
    ImageLoaderData& operator=( ImageLoaderData&& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )