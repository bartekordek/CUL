
#include "PakFilesTests.hpp"
#include "CUL/Filesystem/Archiver.hpp"
#include "CUL/Filesystem/IArchive.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

void PakFilesTests::SetUp()
{
    // Setup code for each test case
}

PakFilesTests::PakFilesTests()
{
    // Constructor code
}

void PakFilesTests::SetUpTestCase()
{
    // Setup code for the entire test case
}

void PakFilesTests::createTestArchive()
{
    CUL::SFile file;
    file.Path = "Info.txt";
    file.PathSize = sizeof( file.Path.getUtfChar() );

    std::ifstream stream( file.Path.getValue(), std::ios::binary | std::ios::ate );
    const auto size = stream.tellg();
    stream.seekg( 0, std::ios::beg );
    const std::size_t fileContentsSize = static_cast<std::size_t>( size );
    auto* buffer = new char[fileContentsSize];
    stream.read( buffer, size );
    file.Content = buffer;
    file.FileSize = static_cast<std::uint64_t>( size );

    CUL::CULInterface::createInstance()->getFS()->deleteFile( "TestArchive.pak" );
    CUL::SFArchiveMetadata meta;
    meta.Path = "TestArchive.pak";
    meta.FilesCount = 1u;
    meta.Files.push_back( file );

    CUL::Archiver::getInstance().createArchive( meta, CUL::EAccesMode::Write );
}

TEST_F( PakFilesTests, basicPakFileWrite )
{
    createTestArchive();
}

TEST_F( PakFilesTests, basicPakFileLoad )
{
    createTestArchive();
    CUL::Archiver::getInstance().
    CUL::Archiver::getInstance().readArchive( "TestArchive.pak" );
}


TEST_F( PakFilesTests, pakFileContainsExpectedData )
{
    // Test code
}

void PakFilesTests::TearDown()
{

}

void PakFilesTests::TearDownTestCase()
{

}

PakFilesTests::~PakFilesTests()
{

}