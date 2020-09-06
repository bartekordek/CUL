#ifdef USE_DEVIL

#include "Graphics/ImageLoaderDevil.hpp"
#include "Graphics/ImageConcrete.hpp"
#include "CUL/Graphics/Color.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/String.hpp"
#include "Graphics/IMPORT_Devil.hpp"

using namespace CUL::Graphics;

void checkForIluErrors();
unsigned roundUpToPowerOfTwo( unsigned value );

DevilImageLoader::DevilImageLoader()
{
    ilInit();
    iluInit();
    ColorS clearColor( ColorE::WHITE );
    ilClearColour(
        clearColor.getRUI(),
        clearColor.getGUI(),
        clearColor.getBUI(),
        clearColor.getAUI() );
    checkForIluErrors();
}

IImage* DevilImageLoader::loadImage( const Path& path, Cbool )
{
    IImage* result = findImage( path );
    ImageInfo ii;
    if( result )
    {
        return result;
    }

    ILuint imgID = 0;
    ilGenImages( 1, &imgID );
    ilBindImage( imgID );

    const auto pathAsCharArray = path.getPath().cStr();
    ILboolean success = ilLoadImage( pathAsCharArray );
    const ILenum ilError = ilGetError();
    if( ilError != IL_NO_ERROR )
    {
        auto errorIluAsString = iluErrorString( ilError );
        CUL::Assert::simple( false, "ILU/ILUT cannot load image, error:" + String( errorIluAsString ) );
    }

    // TODO: Is it really necessary?
    success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
    checkForIluErrors();

    CUL::Assert::simple( success == IL_TRUE, "ILU/ILUT error, cannot convert image." );

    const auto imgWidth = static_cast<unsigned>( ilGetInteger( IL_IMAGE_WIDTH ) );
    const auto imgHeight = static_cast<unsigned>( ilGetInteger( IL_IMAGE_HEIGHT ) );
    ii.depth = 24;//static_cast<int>( ilGetInteger( IL_IMAGE_DEPTH ) );// 24


    iluImageParameter( ILU_PLACEMENT, ILU_UPPER_LEFT );

    //Resize image
    iluEnlargeCanvas(
        static_cast<ILuint>( imgWidth ),
        static_cast<ILuint>( imgHeight ),
        1 );

    const auto imageConcrete = new ImageConcrete();

    ii.size.width = static_cast<int>( imgWidth );
    ii.size.height = static_cast<int>( imgHeight );
    
    ii.pitch = 4 * static_cast<int>( imgWidth ); //1628
    ii.pixelFormat = PixelFormat::RGBA32; //376840196
    ii.path = path;


    auto rawData = ilGetData();

    const auto textureSize = static_cast<size_t>( imgWidth * imgHeight * 4);
    DataType* dataCopy = new DataType[textureSize];

    memcpy(
        dataCopy,
        rawData,
        static_cast<size_t>( textureSize ) );

    imageConcrete->setData( dataCopy );
    imageConcrete->setPath( path );
    imageConcrete->setImageInfo( ii );
    //imageConcrete->disableRelease( true );

    m_fileList[path.getPath()] = std::unique_ptr<IImage>( imageConcrete );

    ilDeleteImages( 1, &imgID );

    result = imageConcrete;

    return result;
}

void DevilImageLoader::deleteImage( const Path& path )
{
    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        m_fileList.erase( it );
    }
}

IImage* DevilImageLoader::findImage( const Path& path )
{
    IImage* result = nullptr;

    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        result = it->second.get();
    }

    return result;
}

void checkForIluErrors()
{
    const ILenum ilError = ilGetError();
    if( ilError != IL_NO_ERROR )
    {
        auto errorIluAsString = iluErrorString( ilError );
        CUL::Assert::simple( false, "ILU/ILUT error:" + CUL::String( errorIluAsString ) );
    }
}

unsigned roundUpToPowerOfTwo( unsigned value )
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

DevilImageLoader::~DevilImageLoader()
{
    ilShutDown();
}

#endif // USE_DEVIL