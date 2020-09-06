#include "Graphics/ImageConcrete.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"

using namespace CUL::Graphics;

ImageConcrete::ImageConcrete()
{
}

DataType* ImageConcrete::getData() const
{
    return m_data;
}

const ImageInfo& ImageConcrete::getImageInfo() const
{
    return m_imageInfo;
}

void ImageConcrete::setPath( const Path& path )
{
    m_imageInfo.path = path;
}

void ImageConcrete::setData( DataType* data)
{
    releaseImage();
    m_data = data;
}

void ImageConcrete::setImageInfo( const ImageInfo& ii )
{
    m_imageInfo = ii;
}

void ImageConcrete::disableRelease( Cbool val )
{
    m_disableRelease = val;
}

ImageConcrete::~ImageConcrete()
{
    releaseImage();
}

void ImageConcrete::releaseImage()
{
    if( !m_disableRelease )
    {
        delete[] m_data;
        m_data = nullptr;
    }
}