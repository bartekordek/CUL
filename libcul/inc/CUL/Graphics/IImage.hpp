#pragma once

#include "CUL/Filesystem/Path.hpp"
#include "CUL/Graphics/SimpleSize2D.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using DataType = unsigned char;
using SSize2Dui = Graphics::SSize2Dui;
using SSize2Di = Graphics::SSize2Di;


enum class PixelFormat: short
{
    NONE = -1,
    RGB = 0x1907,
    RGBA = 0x1908,
    ARGB,
    BGR,
    BGRA,
    ABGR,
    TEST
};

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4251 )
#pragma warning( disable: 4820 )
#endif

class CULLib_API ImageInfo
{
public:
    ImageInfo();

    FS::Path path;
    SSize2Di size;
    SSize2Di canvasSize;
    String colorFormat = "";
    PixelFormat pixelFormat = PixelFormat::NONE;
    int depth = 0;
    int pitch = 0;
    unsigned BPP = 0;
};
#if _MSC_VER
#pragma warning( pop )
#endif

class CULLib_API IImage
{
public:
    explicit IImage();

    virtual DataType* getData() const = 0;
    virtual const ImageInfo& getImageInfo() const = 0;

    virtual ~IImage();
protected:
private:

private: // Deleted
    IImage( IImage&& arg ) = delete;
    IImage( const IImage& value ) = delete;
    IImage& operator=( const IImage& rhv ) = delete;
    IImage& operator=( IImage&& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )