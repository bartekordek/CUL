#include "Graphics/ImageLoaderDevIL.hpp"
#include "Graphics/IMPORT_DevIL.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL;
using namespace Graphics;

ImageLoaderDevil::ImageLoaderDevil()
{
}

unsigned ImageLoaderDevil::powerOfTwo( unsigned num )
{
    if( num != 0 )
    {
        num--;
        num |= ( num >> 1 );   // Or first 2 bits
        num |= ( num >> 2 );   // Or next 2 bits
        num |= ( num >> 4 );   // Or next 4 bits
        num |= ( num >> 8 );   // Or next 8 bits
        num |= ( num >> 16 );  // Or next 16 bits
        num++;
    }

    return num;
}

IImage* ImageLoaderDevil::loadImage( const FS::Path& path, bool )
{
    ILuint imgID = 0;
    ilGenImages( 1, &imgID );
    ilBindImage( imgID );

    ILboolean success = ilLoadImage( path.getPath().cStr() );
    CUL::Assert::simple( success == IL_TRUE, "Cannot load: " + path.getPath() );

    // Convert image to RGBA
    success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
    CUL::Assert::simple( success == IL_TRUE, "Cannot convert: " + path.getPath() );

     // Initialize dimensions
    unsigned imgWidth = (unsigned)ilGetInteger( IL_IMAGE_WIDTH );
    unsigned imgHeight = (unsigned)ilGetInteger( IL_IMAGE_HEIGHT );

    // Calculate required texture dimensions
    unsigned texWidth = powerOfTwo( imgWidth );
    unsigned texHeight = powerOfTwo( imgHeight );

    // Texture is the wrong size
    if( imgWidth != texWidth || imgHeight != texHeight )
    {
        iluImageParameter( ILU_PLACEMENT, ILU_UPPER_LEFT );    // Place image at upper left
        iluEnlargeCanvas( (int)texWidth, (int)texHeight, 1 );  // Resize image
    }

    // Create texture from file pixels
    loadTextureFromPixels32( (GLuint*)ilGetData(), imgWidth, imgHeight, texWidth, texHeight );

    ilDeleteImages( 1, &imgID );

    return nullptr;
}

void ImageLoaderDevil::deleteImage( const FS::Path& path )
{
}

IImage* ImageLoaderDevil::findImage( const FS::Path& path )
{
    return nullptr;
}

ImageLoaderDevil::~ImageLoaderDevil()
{
}