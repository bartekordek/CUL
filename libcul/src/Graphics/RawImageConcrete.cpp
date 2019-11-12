#include "RawImageConcrete.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/Log/ILogContainer.hpp"

using namespace CUL;
using namespace Graphics;

bool RawImageConcrete::s_ilInitialized = false;

RawImageConcrete::RawImageConcrete()
{

}

RawImageConcrete::~RawImageConcrete()
{
    if( this->m_data )
    {
        ilDeleteImages( 1, &this->m_iluId );
        this->m_data = nullptr;
    }
}

void RawImageConcrete::loadFromFile( CUL::CnstMyStr& path )
{
    CUL::LOG::LOG_CONTAINER::getLogger()->log( "RawImageConcrete::loadFromFile" );
    CUL::LOG::LOG_CONTAINER::getLogger()->log( "Path = " + path );

    if( false == RawImageConcrete::s_ilInitialized )
    {
        ilInit();
        iluInit();
        RawImageConcrete::s_ilInitialized = true;
    }

    ilClearColour( 255, 255, 255, 000 );

    ilGenImages( 1, &this->m_iluId );
    ilBindImage( this->m_iluId );
    ILboolean success = ilLoadImage( path.cStr() );

    if( IL_TRUE != success )
    {
        CUL::LOG::LOG_CONTAINER::getLogger()->log(
            "Current dir: " +
            CUL::FS::FSApi::getCurrentDir().string() );
        const auto error = ilGetError();
        CUL::LOG::LOG_CONTAINER::getLogger()->log( "ILU ERROR:", CUL::LOG::Severity::ERROR );
        CUL::LOG::LOG_CONTAINER::getLogger()->log( error, CUL::LOG::Severity::ERROR );
        CUL::LOG::LOG_CONTAINER::getLogger()->log( iluErrorString( error ), CUL::LOG::Severity::ERROR );
        CUL::Assert::simple( false, "Cannot load file: " + path );
    }

    success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );

    if( IL_TRUE != success )
    {
        const auto error = ilGetError();
        CUL::LOG::LOG_CONTAINER::getLogger()->log( "ILU ERROR:", CUL::LOG::Severity::ERROR );
        CUL::LOG::LOG_CONTAINER::getLogger()->log( "error", CUL::LOG::Severity::ERROR );
        CUL::LOG::LOG_CONTAINER::getLogger()->log( iluErrorString( error ), CUL::LOG::Severity::ERROR );
        CUL::Assert::simple( false, "Cannot convert image: " + path );
    }
    auto imgWidth = ( unsigned int ) ilGetInteger( IL_IMAGE_WIDTH );
    auto imgHeight = ( unsigned int ) ilGetInteger( IL_IMAGE_HEIGHT );

    this->m_size.setXYZ( imgWidth, imgHeight, 0 );
    auto dataPtr = ilGetData();
    this->m_data = static_cast< RawDataPtr >( dataPtr );
}

cunt RawImageConcrete::getID() const
{
    return this->m_fileId;
}

const Math::Vector3Du& RawImageConcrete::getSize() const
{
    return this->m_size;
}

RawDataPtr RawImageConcrete::getData() const
{
    return this->m_data;
}