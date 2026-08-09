#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/Filesystem/RegularFile.hpp"
#include "CSVFile.hpp"
#include "CUL/Graphics/IImageLoader.hpp"
#include "Graphics/ImageConcrete.hpp"
#include "CUL/GenericUtils/SimpleAssert.hpp"
#include "CUL/Profiling/Profiler.hpp"

using namespace CUL;

using IFile = FS::IFile;
using FileFactory = FS::FileFactory;
using ICSVFile = FS::ICSVFile;
using JSONFile = JSON::JSONFile;

FileFactory::FileFactory( CULInterface* culInterface ) : m_culInterface( culInterface )
{
}

IFile* FileFactory::createFileFromPath( const Path& path )
{
    CUL::StringWr ext = path.getExtension();
    ext.toLower();

    if( ext.equals( "bmp" ) || ext.equals( ".bmp" ) || ext.equals( "jpg" ) ||
        ext.equals( ".jpg" ) || ext.equals( "jpeg" ) || ext.equals( ".jpeg" ) ||
        ext.equals( "png" ) || ext.equals( ".png" ) )
    {
        CUL::Assert::simple( false, "Not implemented." );
        return nullptr;
    }

    return createRegularFileRawPtr( path );
}

IFile* FileFactory::createRegularFileRawPtr( const Path& path )
{
    ProfilerScope( "FileFactory::createRegularFileRawPtr" );

    auto file = new RegularFile( path.getPath(), m_culInterface );
    return file;
}

ICSVFile* FileFactory::createCSVFileRawPtr( const Path& path )
{
    auto csvFile = new CSVFile( path, m_culInterface );
    return csvFile;
}

FS::JSONFilePtr FileFactory::createJSONFileRawPtr( const Path& path )
{
    auto result = new JSON::JSONFile( path, m_culInterface );
    FS::JSONFilePtr file;
    file.reset( result );
    return file;
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