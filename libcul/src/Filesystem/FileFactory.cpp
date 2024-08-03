#include "CUL/Filesystem/FileFactory.hpp"
#include "FileRegularImpl.hpp"
#include "CSVFile.hpp"
#include "JSON/JSONFileConcrete.hpp"
#include "CUL/Graphics/IImageLoader.hpp"
#include "Graphics/ImageConcrete.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"

#include "CUL/IMPORT_tracy.hpp"

using namespace CUL;

using IFile = FS::IFile;
using FileFactory = FS::FileFactory;
using ICSVFile = FS::ICSVFile;
using IJSONFile = JSON::IJSONFile;

FileFactory::FileFactory( CULInterface* culInterface ):
    m_culInterface( culInterface )
{

}

IFile* FileFactory::createFileFromPath( const Path& path )
{
    auto ext = path.getExtension();
    ext.toLower();
    if( ext == ".csv" )
    {
        return createJSONFileRawPtr( path );
    }
    else if( ext == ".json" )
    {
        return createJSONFileRawPtr( path );
    }
    else if(
        ext == ".bmp" ||
        ext == ".png" ||
        ext == ".jpg" ||
        ext == ".jpeg" )
    {
        CUL::Assert::simple( false, "Not implemented." );
        return nullptr;
    }
    else
    {
        return createRegularFileRawPtr( path );
    }
}

IFile* FileFactory::createRegularFileRawPtr( const Path& path )
{
    ZoneScoped;
    auto file = new FileRegularImpl( path.getPath(), m_culInterface );
    return file;
}

ICSVFile* FileFactory::createCSVFileRawPtr( const Path& path )
{
    auto csvFile = new CSVFile( path, m_culInterface );
    return csvFile;
}

IJSONFile* FileFactory::createJSONFileRawPtr( const Path& path )
{
    auto fc = FS::FileFactory::createRegularFileRawPtr( path );
    auto result = new JSON::JSONFileConcrete( path, fc, m_culInterface );
    return result;
}

Graphics::IImage* FileFactory::createRawImageRawPtr( const Path& path )
{
    const auto il = m_culInterface->getImageLoader();
    return il->loadImage( path );
}

// TODO
CUL::Graphics::IImage* FileFactory::createRawImageRawPtr()
{
    return new CUL::Graphics::ImageConcrete();
}