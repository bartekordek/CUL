#include "CUL/Graphics/IImage.hpp"

using namespace CUL::Graphics;

ImageInfo::ImageInfo()
{
}

ImageInfo::ImageInfo( const ImageInfo& arg ):
    path( arg.path ),
    size( arg.size ),
    colorFormat( arg.colorFormat )
{
}

ImageInfo::ImageInfo( ImageInfo&& arg ):
    path( std::move( arg.path ) ),
    size( std::move( arg.size ) ),
    colorFormat( std::move( arg.colorFormat ) )
{
}

ImageInfo& ImageInfo::operator=( const ImageInfo& rhv )
{
    if( this != &rhv )
    {
        path = rhv.path;
        size = rhv.size;
        colorFormat = rhv.colorFormat;
    }
    return *this;
}

ImageInfo& ImageInfo::operator=( ImageInfo&& rhv )
{
    if( this != &rhv )
    {
        path = std::move( rhv.path );
        size = std::move( rhv.size );
        colorFormat = std::move( rhv.colorFormat );
    }
    return *this;
}

IImage::IImage()
{

}

IImage::~IImage()
{
}