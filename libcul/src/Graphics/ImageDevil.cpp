#include "Graphics/ImageDevil.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

using namespace CUL::Graphics;

ImageDevil::ImageDevil()
{
}

const DataType* ImageDevil::getData() const
{
    return m_data;
}

const ImageInfo& ImageDevil::getImageInfo() const
{
    return m_imageInfo;
}

void ImageDevil::setPath( const Path& path )
{
    m_imageInfo.path = path;
}

void ImageDevil::setData( ILubyte* data, Cunt width, Cunt height )
{
    releaseImage();

    auto textureSize = width * height;
    m_data = new DataType[ textureSize ];
    memcpy( m_data, data, textureSize * 4 );
}

void ImageDevil::setImageInfo( const ImageInfo& ii )
{
    m_imageInfo = ii;
}

ImageDevil::~ImageDevil()
{
    releaseImage();
}

void ImageDevil::releaseImage()
{
    delete[] m_data;
    m_data = nullptr;
}