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

void ImageDevil::setData( const ILubyte* data, Cunt width, Cunt height )
{
    releaseImage();

    const auto textureSize = static_cast<size_t>( width * height );
    m_data = new DataType[textureSize];
    memcpy(
        m_data,
        data,
        static_cast<size_t>( textureSize * 4 ) );
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