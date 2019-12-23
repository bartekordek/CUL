#include "IImage.hpp"

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