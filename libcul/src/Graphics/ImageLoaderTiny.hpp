#pragma once

#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class TinyImageLoader final:
    public IImageLoader
{
public:
    TinyImageLoader();

    IImage* loadImage( const Path& path, Cbool rgba = false ) override;
    void deleteImage( const Path& path ) override;
    IImage* findImage( const Path& path ) override;

    ~TinyImageLoader();

protected:

private:
    using FileList = std::map<String, std::unique_ptr<IImage>>;
    FileList m_fileList;

private: // Deleted
    TinyImageLoader( const TinyImageLoader& arg ) = delete;
    TinyImageLoader( TinyImageLoader&& arg ) = delete;
    TinyImageLoader& operator=( const TinyImageLoader& rhv ) = delete;
    TinyImageLoader& operator=( TinyImageLoader&& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )