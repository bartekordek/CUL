#pragma once

#include "CUL/Graphics/IImage.hpp"
#include "CUL/GenericUtils/IConfigFile.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class CULLib_API IImageLoader
{
public:
    IImageLoader();
    virtual ~IImageLoader();

    virtual IImage* loadImage( const FS::Path& path, Cbool rgba = false );
    virtual IImage* loadImage(DataType * data, unsigned width, unsigned height );
    virtual IImage* findImage( const FS::Path& path ) = 0;
    virtual void deleteImage( const FS::Path& path ) = 0;

    static IImageLoader* createConcrete( CUL::GUTILS::IConfigFile* config = nullptr );

protected:
private: // Deleted
    IImageLoader( const IImageLoader& arg ) = delete;
    IImageLoader& operator=( const IImageLoader& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )