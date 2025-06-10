#pragma once

#include "CUL/Graphics/IImage.hpp"
#include "CUL/STL_IMPORTS/STD_functional.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4820 )
#endif

class ImageConcrete final:
    public IImage
{
public:
    ImageConcrete();

    DataType* getData() const override;
    const ImageInfo& getImageInfo() const override;

    void setPath( const FS::Path& path );
    void setData( DataType* data );
    void setData( DataType* data, std::function<void(void*)> deleter );
    void setImageInfo( const ImageInfo& ii );

    ~ImageConcrete();

protected:
private:
    void releaseImage();

    ImageInfo m_imageInfo;
    DataType* m_data = nullptr;
    std::function<void(void*)> m_deleter;

private: // Deleted
    ImageConcrete( const ImageConcrete& arg ) = delete;
    ImageConcrete& operator=( const ImageConcrete& rhv ) = delete;
    ImageConcrete( ImageConcrete&& arg ) = delete;
    ImageConcrete& operator=( ImageConcrete&& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )