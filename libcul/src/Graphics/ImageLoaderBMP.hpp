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
    ImageLoaderBMP( CULInterface* culInterface );

    IImage* loadImage( const FS::Path& path, bool rgba = false ) override;
    IImage* loadImage2( const FS::Path& path, bool rgba = false ) ;
    void printFileSize( const FS::Path& path );
    void deleteImage( const FS::Path& path ) override;
    IImage* findImage( const FS::Path& path ) override;

    ~ImageLoaderBMP();

protected:

private:
    using FileList = std::map<StringWr, std::unique_ptr<IImage>>;
    FileList m_fileList;

private: // Deleted
    ImageLoaderBMP( const ImageLoaderBMP& arg ) = delete;
    ImageLoaderBMP( ImageLoaderBMP&& arg ) = delete;
    ImageLoaderBMP& operator=( const ImageLoaderBMP& rhv ) = delete;
    ImageLoaderBMP& operator=( ImageLoaderBMP&& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )