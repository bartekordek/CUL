#pragma once

#include "CUL/Graphics/IImage.hpp"
#include "Graphics/IMPORT_Devil.hpp"

NAMESPACE_BEGIN( CUL )
NAMESPACE_BEGIN( Graphics )

using Cunt = CUL::Cunt;

class ImageDevil final:
    public IImage
{
public:
    ImageDevil();

    const DataType* getData() const override;
    const ImageInfo& getImageInfo() const override;

    void setPath( const Path& path );
    void setData( const ILubyte* data, Cunt width, Cunt height );
    void setImageInfo( const ImageInfo& ii );

    ~ImageDevil();

protected:
private:
    void releaseImage();

    ImageInfo m_imageInfo;
    DataType* m_data = nullptr;

private: // Deleted
    ImageDevil( const ImageDevil& arg ) = delete;
    ImageDevil& operator=( const ImageDevil& rhv ) = delete;
};

NAMESPACE_END( Graphics )
NAMESPACE_END( CUL )