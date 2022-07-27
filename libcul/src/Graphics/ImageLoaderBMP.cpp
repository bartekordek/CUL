#include "Graphics/ImageLoaderBMP.hpp"

#include "Graphics/ImageConcrete.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"
#include "CUL/STL_IMPORTS/STD_vector.hpp"
#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;
using namespace Graphics;

uint32_t row_stride = 0;

#if _MSC_VER
#pragma warning( push )
//#pragma warning( disable: 4251 )
//#pragma warning( disable: 4820 )
#pragma warning( disable: 5045 )
#endif

// Done with:
// https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/
#pragma pack(push, 1) // Align left, no wrap.
struct BMPFileHeader
{
    uint16_t file_type{ 0x4D42 };          // File type always BM which is 0x4D42 (stored as hex uint16_t in little endian)
    uint32_t file_size{ 0 };               // Size of the file (in bytes)
    uint16_t reserved1{ 0 };               // Reserved, always 0
    uint16_t reserved2{ 0 };               // Reserved, always 0
    uint32_t offset_data{ 0 };             // Start position of pixel data (bytes from the beginning of the file)
};

#pragma pack(push, 1) // Align left, no wrap.
struct BMPInfoHeader
{
    uint32_t size{ 0 }; // Size of this header (in bytes)
    int32_t width{ 0 }; // width of bitmap in pixels
    int32_t height{ 0 }; // width of bitmap in pixels
    //       (if positive, bottom-up, with origin in lower left corner)
    //       (if negative, top-down, with origin in upper left corner)
    uint16_t planes{ 1 }; // No. of planes for the target device, this is always 1
    uint16_t bit_count{ 0 }; // No. of bits per pixel
    uint32_t compression{ 0 }; // 0 or 3 - uncompressed. THIS PROGRAM CONSIDERS ONLY UNCOMPRESSED BMP images
    uint32_t size_image{ 0 }; // 0 - for uncompressed images
    int32_t x_pixels_per_meter{ 0 };
    int32_t y_pixels_per_meter{ 0 };
    uint32_t colors_used{ 0 }; // No. color indexes in the color table. Use 0 for the max number of colors allowed by bit_count
    uint32_t colors_important{ 0 }; // No. of colors used for displaying the bitmap. If 0 all colors are required
};

struct BMPColorHeader
{
    // Bit mask for the red channel
    uint32_t red_mask{ 0x00ff0000 };
    // Bit mask for the green channel
    uint32_t green_mask{ 0x0000ff00 };
    // Bit mask for the blue channel
    uint32_t blue_mask{ 0x000000ff };
    // Bit mask for the alpha channel
    uint32_t alpha_mask{ 0xff000000 };
    // Default "sRGB" (0x73524742)
    uint32_t color_space_type{ 0x73524742 };
    // Unused data for sRGB color space
    uint32_t unused[16]{ 0 };
};


ImageLoaderBMP::ImageLoaderBMP( CULInterface* culInterface ) : IImageLoader( culInterface )
{

}

void checkColorHeader( BMPColorHeader& bmp_color_header );
uint32_t makeStrideAligned( uint32_t align_stride );

IImage* ImageLoaderBMP::loadImage2( const FS::Path& path, bool )
{
    printFileSize( path );

    auto result =  new ImageConcrete();

    ImageInfo imageInfo;
    imageInfo.path = path;

    std::ifstream inp{ path.getPath().cStr(), std::ios_base::binary };

    BMPFileHeader fileHeader;

    inp.read((char*)&fileHeader, sizeof(fileHeader));

    if( fileHeader.file_type != 0x4D42 )
    {
        CUL::Assert::simple( false, "Error! Unrecognized file format, file: " + path.getPath() );
    }

    BMPInfoHeader infoHeader;
    inp.read( (char*) &infoHeader, sizeof( infoHeader ) );

    imageInfo.size = {
        infoHeader.width,
        infoHeader.height
    };

    imageInfo.depth = infoHeader.bit_count;
    imageInfo.pitch = 4 * infoHeader.width;
    imageInfo.pixelFormat = PixelFormat::RGBA;

    BMPColorHeader bmpColorHeader;
    // The BMPColorHeader is used only for transparent images
    if( infoHeader.bit_count == 32 )
    {
        // Check if the file has bit mask color information
        if( infoHeader.size >= ( sizeof( BMPInfoHeader ) + sizeof( BMPColorHeader ) ) )
        {
            inp.read( (char*) &bmpColorHeader, sizeof( bmpColorHeader ) );
            // Check if the pixel data is stored as BGRA and if the color space type is sRGB
            checkColorHeader( bmpColorHeader );

        }
        else
        {
            CUL::Assert::simple( false, "Warning! The file \"" + path.getPath() + "\" does not seem to contain bit mask information\n" );
        }
    }

    // Adjust the header fields for output.
    // Some editors will put extra info in the image file, we only save the headers and the data.
    if( infoHeader.bit_count == 32 )
    {
        infoHeader.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
        fileHeader.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
    }
    else
    {
        infoHeader.size = sizeof(BMPInfoHeader);
        fileHeader.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
    }
    fileHeader.file_size = fileHeader.offset_data;

    if( infoHeader.height < 0 )
    {
        CUL::Assert::simple( false, "The program can treat only BMP images with the origin in the bottom left corner!" );
    }

    // Jump to the pixel data location
    inp.seekg(fileHeader.offset_data, inp.beg);

    // Adjust the header fields for output.
    // Some editors will put extra info in the image file, we only save the headers and the data.
    if( infoHeader.bit_count == 32 )
    {
        infoHeader.size = sizeof( BMPInfoHeader ) + sizeof( BMPColorHeader );
        fileHeader.offset_data = sizeof( BMPFileHeader ) + sizeof( BMPInfoHeader ) + sizeof( BMPColorHeader );
    }
    else
    {
        infoHeader.size = sizeof( BMPInfoHeader );
        fileHeader.offset_data = sizeof( BMPFileHeader ) + sizeof( BMPInfoHeader );
    }
    fileHeader.file_size = fileHeader.offset_data;

    if( infoHeader.height < 0 )
    {
        throw std::runtime_error( "The program can treat only BMP images with the origin in the bottom left corner!" );
    }

    const auto imageDataSize = infoHeader.size_image;
    char* data = new char[imageDataSize];
    DataType* imageData = new DataType[ imageDataSize ];

    // Here we check if we need to take into account row padding
    if( infoHeader.width % 4 == 0 )
    {
        inp.read( (char*) data,
                  std::streamsize( imageDataSize ) );

        for( auto i = 0u; i < imageDataSize; ++i )
        {
            const auto value = data[i];
            const auto converted = static_cast<DataType>( value );
            imageData[i] = converted;
        }

        fileHeader.file_size += static_cast<uint32_t>( imageDataSize );
    }
    else
    {
        row_stride = infoHeader.width * infoHeader.bit_count / 8u;
        uint32_t new_stride = makeStrideAligned( 4 );
        std::vector<uint8_t> padding_row( new_stride - row_stride );

        const int infoHeaderHeight = infoHeader.height;
        for( int y = 0; y < infoHeaderHeight; ++y )
        {
            unsigned offset = row_stride * y;
            unsigned ptr = (unsigned)data + offset;
            inp.read( (char*)( ptr ), row_stride );
            inp.read( (char*) padding_row.data(), ( std::streamsize ) padding_row.size() );
        }
        fileHeader.file_size += static_cast<uint32_t>( imageDataSize ) + infoHeader.height * static_cast<uint32_t>( padding_row.size() );
    }

    result->setData( imageData );
    result->setImageInfo( imageInfo );

    return result;
}

void check_color_header( BMPColorHeader& bmp_color_header );
uint32_t make_stride_aligned( uint32_t align_stride );

IImage* ImageLoaderBMP::loadImage( const FS::Path& path, bool )
{
    auto result = new ImageConcrete();
    ImageInfo imageInfo;
    imageInfo.path = path;

    return result;
}

IImage* loadImage2( const FS::Path& path, bool )
{
    auto result = new ImageConcrete();
    ImageInfo imageInfo;
    imageInfo.path = path;
    std::ifstream inp{ path.getPath().cStr(), std::ios_base::binary };
    if( inp )//458 rezygnuje z uslugi
    {
        std::cout << "uint16_t size = " << sizeof( uint16_t ) << "\n";
        std::cout << "uint32_t size = " << sizeof( uint32_t ) << "\n";;

        BMPFileHeader file_header;
        inp.read( (char*) &file_header, sizeof( file_header ) );
        if( file_header.file_type != 0x4D42 )
        {
            throw std::runtime_error( "Error! Unrecognized file format." );
        }
        BMPInfoHeader bmp_info_header;
        inp.read( (char*) &bmp_info_header, sizeof( bmp_info_header ) );

        imageInfo.size = {
            bmp_info_header.width,
            bmp_info_header.height
        };

        imageInfo.depth = bmp_info_header.bit_count;
        imageInfo.pitch = 4 * bmp_info_header.width;
        imageInfo.pixelFormat = PixelFormat::RGBA;

        BMPColorHeader bmp_color_header;
        // The BMPColorHeader is used only for transparent images
        if( bmp_info_header.bit_count == 32 )
        {
            // Check if the file has bit mask color information
            if( bmp_info_header.size >= ( sizeof( BMPInfoHeader ) + sizeof( BMPColorHeader ) ) )
            {
                inp.read( (char*) &bmp_color_header, sizeof( bmp_color_header ) );
                // Check if the pixel data is stored as BGRA and if the color space type is sRGB
                check_color_header( bmp_color_header );
            }
            else
            {
                std::cerr << "Error! The file \"" << path.getPath().cStr() << "\" does not seem to contain bit mask information\n";
                throw std::runtime_error( "Error! Unrecognized file format." );
            }
        }

        // Jump to the pixel data location
        inp.seekg( file_header.offset_data, inp.beg );

        // Adjust the header fields for output.
        // Some editors will put extra info in the image file, we only save the headers and the data.
        if( bmp_info_header.bit_count == 32 )
        {
            bmp_info_header.size = sizeof( BMPInfoHeader ) + sizeof( BMPColorHeader );
            file_header.offset_data = sizeof( BMPFileHeader ) + sizeof( BMPInfoHeader ) + sizeof( BMPColorHeader );
        }
        else
        {
            bmp_info_header.size = sizeof( BMPInfoHeader );
            file_header.offset_data = sizeof( BMPFileHeader ) + sizeof( BMPInfoHeader );
        }
        file_header.file_size = file_header.offset_data;

        if( bmp_info_header.height < 0 )
        {
            throw std::runtime_error( "The program can treat only BMP images with the origin in the bottom left corner!" );
        }

        const auto dataSize = bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8u;
        DataType* data = new DataType[dataSize];
        std::memset( data, '0', dataSize );

        // Here we check if we need to take into account row padding
        if( bmp_info_header.width % 4 == 0 )
        {
            char* dataAsChar = new char[dataSize];
            inp.read(
                dataAsChar,
                ( std::streamsize ) dataSize );

            for( unsigned int i = 0; i < dataSize; ++i )
            {
                const auto val = data[i];
                const auto converted = static_cast<DataType>( val );
                data[i] = converted;
            }

            file_header.file_size += static_cast<uint32_t>( dataSize );
        }
        else
        {
            row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8u;
            uint32_t new_stride = make_stride_aligned( 4 );
            std::vector<uint8_t> padding_row( new_stride - row_stride );

            for( int y = 0; y < bmp_info_header.height; ++y )
            {
                inp.read( (char*) ( data + row_stride * y ), row_stride );
                inp.read(
                    (char*) padding_row.data(),
                    ( std::streamsize ) padding_row.size() );
            }
            file_header.file_size += static_cast<uint32_t>( dataSize ) + bmp_info_header.height * static_cast<uint32_t>( padding_row.size() );
        }

        result->setData( data );
        result->setImageInfo( imageInfo );
    }
    else
    {
        throw std::runtime_error( "Unable to open the input image file." );
    }

    return result;
}

uint32_t make_stride_aligned( uint32_t align_stride )
{
    uint32_t new_stride = row_stride;
    while( new_stride % align_stride != 0 )
    {
        new_stride++;
    }
    return new_stride;
}

void check_color_header( BMPColorHeader& bmp_color_header )
{
    BMPColorHeader expected_color_header;
    if( expected_color_header.red_mask != bmp_color_header.red_mask ||
        expected_color_header.blue_mask != bmp_color_header.blue_mask ||
        expected_color_header.green_mask != bmp_color_header.green_mask ||
        expected_color_header.alpha_mask != bmp_color_header.alpha_mask )
    {
        throw std::runtime_error( "Unexpected color mask format! The program expects the pixel data to be in the BGRA format" );
    }
    if( expected_color_header.color_space_type != bmp_color_header.color_space_type )
    {
        throw std::runtime_error( "Unexpected color space type! The program expects sRGB values" );
    }
}

void ImageLoaderBMP::printFileSize( const FS::Path& path )
{
    const auto fileSize = path.getFileSize();
    std::cout << "FILESIZE = " << fileSize << "\n";

    std::cout << "uint16_t size = " << sizeof( uint16_t ) << "\n";
    std::cout << "uint32_t size = " << sizeof( uint32_t ) << "\n";
}

void checkColorHeader( BMPColorHeader& bmp_color_header )
{
    BMPColorHeader expected_color_header;
    if( expected_color_header.red_mask != bmp_color_header.red_mask ||
        expected_color_header.blue_mask != bmp_color_header.blue_mask ||
        expected_color_header.green_mask != bmp_color_header.green_mask ||
        expected_color_header.alpha_mask != bmp_color_header.alpha_mask )
    {
        CUL::Assert::simple( false, "Unexpected color mask format! The program expects the pixel data to be in the BGRA format" );
    }
    if( expected_color_header.color_space_type != bmp_color_header.color_space_type )
    {
        CUL::Assert::simple( false, "Unexpected color space type! The program expects sRGB values" );
    }
}

uint32_t makeStrideAligned( uint32_t align_stride )
{
    uint32_t new_stride = row_stride;
    while( new_stride % align_stride != 0 )
    {
        ++new_stride;
    }
    return new_stride;
}

void ImageLoaderBMP::deleteImage( const FS::Path& path )
{
    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        m_fileList.erase( it );
    }
}

IImage* ImageLoaderBMP::findImage( const FS::Path& path )
{
    IImage* result = nullptr;

    auto it = m_fileList.find( path.getPath() );
    if( it != m_fileList.end() )
    {
        result = it->second.get();
    }

    return result;
}

ImageLoaderBMP::~ImageLoaderBMP()
{

}


#if _MSC_VER
__pragma( warning( pop ) )
#endif