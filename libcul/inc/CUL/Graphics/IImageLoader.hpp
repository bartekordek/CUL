#pragma once

#include "CUL/Graphics/IImage.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

class CULLib_API IImageLoader
{
public:
    IImageLoader();
    virtual ~IImageLoader();

    virtual IImage* loadImage( const Path& path, Cbool rgba = false ) = 0;
    virtual IImage* findImage( const Path& path ) = 0;
    virtual void deleteImage( const Path& path ) = 0;

    static IImageLoader* createConcrete();

protected:
private: // Deleted
    IImageLoader( const IImageLoader& arg ) = delete;
    IImageLoader& operator=( const IImageLoader& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )