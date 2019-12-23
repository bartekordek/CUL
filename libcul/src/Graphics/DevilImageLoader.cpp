#include "Graphics/DevilImageLoader.hpp"
#include "Graphics/ImageDevil.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/String.hpp"


using namespace CUL::Graphics;

void checkForIluErrors();
const unsigned roundUpToPowerOfTwo( unsigned value );

DevilImageLoader::DevilImageLoader()
{
    ilInit();
    iluInit();
    ilClearColour( 255, 255, 255, 000 );
    checkForIluErrors();
}

DevilImageLoader::~DevilImageLoader()
{
}

IImage* DevilImageLoader::loadImage( const Path& path )
{
    IImage* result = findImage( path );
    ImageInfo imageInfo;
    if( result )
    {
        return result;
    }

    ILuint imgID = 0;
    ilGenImages( 1, &imgID );
    ilBindImage( imgID );

    ILboolean success = ilLoadImage( path.getPath().cStr() );
    ILenum ilError = ilGetError();
    if( ilError != IL_NO_ERROR )
    {
        auto errorIluAsString = iluErrorString( ilError );
        CUL::Assert::simple( false, "ILU/ILUT cannot load image, error:" + String( errorIluAsString ) );
    }

    // TODO: Is it really necessary?
    success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
    checkForIluErrors();
    imageInfo.colorFormat = "RGBA";
    CUL::Assert::simple( success == IL_TRUE, "ILU/ILUT error, cannot convert image." );

    auto imgWidth = static_cast<unsigned>( ilGetInteger( IL_IMAGE_WIDTH ) );
    auto imgHeight = static_cast<unsigned>( ilGetInteger( IL_IMAGE_HEIGHT ) );

    auto roundedUpWidth = roundUpToPowerOfTwo( imgWidth );
    auto roundedUpHeight = roundUpToPowerOfTwo( imgHeight );

    if( imgWidth != roundedUpWidth || imgHeight != roundedUpHeight )
    {
        //Place image at upper left
        iluImageParameter( ILU_PLACEMENT, ILU_UPPER_LEFT );

        //Resize image
        iluEnlargeCanvas(
            static_cast<ILuint>( roundedUpWidth ),
            static_cast<ILuint>( roundedUpHeight ),
            1 );
    }
    auto iluImage = new ImageDevil();
    imageInfo.size.width = roundedUpWidth;
    imageInfo.size.height = roundedUpHeight;
    iluImage->setData( ilGetData(), roundedUpWidth, roundedUpHeight );
    iluImage->setPath( path );
    iluImage->setImageInfo( imageInfo );

    m_fileList[ path.getPath() ] = iluImage;

    ilDeleteImages( 1, &imgID );

    result = iluImage;

    return result;
}

void DevilImageLoader::deleteImage( const Path& path )
{
    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        delete it->second;
        m_fileList.erase( it );
    }
}

IImage* DevilImageLoader::findImage( const Path& path )
{
    IImage* result = nullptr;

    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        result = it->second;
    }

    return result;
}

void checkForIluErrors()
{
    ILenum ilError = ilGetError();
    if( ilError != IL_NO_ERROR )
    {
        auto errorIluAsString = iluErrorString( ilError );
        CUL::Assert::simple( false, "ILU/ILUT error:" + CUL::String( errorIluAsString ) );
    }
}

const unsigned int roundUpToPowerOfTwo( unsigned value )
{
    if( value != 0 )
    {
        value--;
        value |= ( value >> 1 ); //Or first 2 bits
        value |= ( value >> 2 ); //Or next 2 bits
        value |= ( value >> 4 ); //Or next 4 bits
        value |= ( value >> 8 ); //Or next 8 bits
        value |= ( value >> 16 ); //Or next 16 bits
        value++;
    }

    return value;
}