#pragma once

#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class STBIImageLoader final:
    public IImageLoader
{
public:
    STBIImageLoader( CULInterface* culInterface );

    IImage* loadImage( const FS::Path& path, bool rgba = false ) override;
    void deleteImage( const FS::Path& path ) override;
    IImage* findImage( const FS::Path& path ) override;

    ~STBIImageLoader();

protected:

private:
    using FileList = std::map<String, std::unique_ptr<IImage>>;
    FileList m_fileList;

private: // Deleted
    STBIImageLoader( const STBIImageLoader& arg ) = delete;
    STBIImageLoader( STBIImageLoader&& arg ) = delete;
    STBIImageLoader& operator=( const STBIImageLoader& rhv ) = delete;
    STBIImageLoader& operator=( STBIImageLoader&& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )