#pragma once

#include "CUL/Graphics/IImage.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using Cunt = CUL::Cunt;

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

    void setPath( const Path& path );
    void setData( DataType* data );
    void setImageInfo( const ImageInfo& ii );

    ~ImageConcrete();

protected:
private:
    void releaseImage();

    ImageInfo m_imageInfo;
    DataType* m_data = nullptr;

private: // Deleted
    ImageConcrete( const ImageConcrete& arg ) = delete;
    ImageConcrete& operator=( const ImageConcrete& rhv ) = delete;
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )