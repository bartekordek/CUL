#pragma once

#include "CUL/Graphics/IImageLoader.hpp"
#include "CUL/STL_IMPORTS/STD_map.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class DevilImageLoader final:
    public IImageLoader
{
public:
    DevilImageLoader();
    ~DevilImageLoader();

    IImage* loadImage( const Path& path ) override;
    void deleteImage( const Path& path ) override;
    IImage* findImage( const Path& path ) override;

protected:

private:
    using FileList = std::map<String, std::unique_ptr<IImage>>;
    FileList m_fileList;

private: // Deleted
    DevilImageLoader( const DevilImageLoader& arg ) = delete;
    DevilImageLoader& operator=( const DevilImageLoader& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )