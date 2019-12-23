#pragma once

#include "CUL/Filesystem/Path.hpp"
#include "CUL/Graphics/SimpleSize2D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using DataType = unsigned int*;
using SSize2Dui = Graphics::SSize2Dui;
using Path = FS::Path;

struct CULLib_API ImageInfo
{
    ImageInfo();
    ImageInfo( const ImageInfo& arg );
    ImageInfo& operator=( const ImageInfo& rhv );

    Path path;
    SSize2Dui size;
    String colorFormat;
};

class CULLib_API IImage
{
public:
    IImage() = default;

    virtual const DataType* getData() const = 0;
    virtual const ImageInfo& getImageInfo() const = 0;

    virtual ~IImage() = default;

protected:
private:

private: // Deleted
    IImage( const IImage& value ) = delete;
    IImage& operator=( const IImage& rhv ) = delete;

};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )