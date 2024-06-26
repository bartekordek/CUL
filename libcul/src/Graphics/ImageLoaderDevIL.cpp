#include "Graphics/ImageLoaderDevIL.hpp"
#include "Graphics/IMPORT_DevIL.hpp"
#include "Graphics/ImageConcrete.hpp"

#include "CUL/CULInterface.hpp"
#include "CUL/Log/ILogger.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

using namespace CUL;
using namespace Graphics;

ImageLoaderDevil::ImageLoaderDevil( CULInterface* culInterface ) : IImageLoader( culInterface )
{
    ilInit();
    iluInit();
    ilClearColour( 255, 255, 255, 000 );
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
        iluEnlargeCanvas( (ILuint)texWidth, (ILuint)texHeight,
                          1 );  // Resize image
    }

    ImageConcrete* newImage = new ImageConcrete();
    auto imgDataSize = (size_t)ilGetInteger( IL_IMAGE_SIZE_OF_DATA );
    ILubyte* source = ilGetData();
    auto sizeOfType = sizeof( decltype( *source ) );
    auto sizeOfType2 = sizeof( ILubyte );
    size_t amountToCopy = sizeOfType * imgDataSize;

    ILubyte* dataCopy = new ILubyte[imgDataSize];
    memcpy( dataCopy, source, amountToCopy );
    newImage->setData( static_cast<CUL::Graphics::DataType*>( dataCopy ) );
    newImage->setPath( path );
    CUL::Graphics::ImageInfo imageInfo;
    imageInfo.colorFormat = "?";
    imageInfo.depth = ilGetInteger( IL_IMAGE_DEPTH );
    auto formatName = ilGetString( IL_IMAGE_FORMAT );
    if( formatName )
    {
        getInterface()->getLogger()->log( "No format." );
        sizeOfType2 = sizeOfType2 / 2;
    }
    imageInfo.size.width =
        static_cast<decltype( imageInfo.size.width )>( imgWidth );
    imageInfo.size.height =
        static_cast<decltype( imageInfo.size.height )>( imgHeight );
    imageInfo.canvasSize.width =
        static_cast<decltype( imageInfo.canvasSize.width )>( texWidth );
    imageInfo.canvasSize.height =
        static_cast<decltype( imageInfo.canvasSize.height )>( texHeight );
    imageInfo.BPP =
        static_cast<decltype( imageInfo.BPP )>( ilGetInteger( IL_IMAGE_BPP ) );

    newImage->setImageInfo( imageInfo );

    ilDeleteImages( 1, &imgID );

    return newImage;
}

void ImageLoaderDevil::loadTextureFromPixels32( unsigned*, unsigned, unsigned, unsigned, unsigned )
{
}

void ImageLoaderDevil::deleteImage( const FS::Path& )
{
}

IImage* ImageLoaderDevil::findImage( const FS::Path& )
{
    return nullptr;
}

ImageLoaderDevil::~ImageLoaderDevil()
{
}