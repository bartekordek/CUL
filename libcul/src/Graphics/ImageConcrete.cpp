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

void ImageConcrete::setPath( const FS::Path& path )
{
    m_imageInfo.path = path;
}

void ImageConcrete::setData( DataType* data )
{
    releaseImage();
    m_data = data;
}

void ImageConcrete::setData( DataType* data, std::function<void(void*)> deleter )
{
    releaseImage();
    m_data = data;
    m_deleter = deleter;
}

void ImageConcrete::setImageInfo( const ImageInfo& ii )
{
    m_imageInfo = ii;
}

ImageConcrete::~ImageConcrete()
{
    releaseImage();
}

void ImageConcrete::releaseImage()
{
    if( m_deleter )
    {
        m_deleter( m_data );
    }
    else
    {
        delete[] m_data;
    }

    m_data = nullptr;
}