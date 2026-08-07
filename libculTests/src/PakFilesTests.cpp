
#include "PakFilesTests.hpp"
#include "CUL/Filesystem/Archiver.hpp"
#include "CUL/Filesystem/IArchive.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/Filesystem/FSApi.hpp"
#include "CUL/STL_IMPORTS/STD_cstring.hpp"
#include "CUL/STL_IMPORTS/STD_fstream.hpp"

class SimpleFile
{
public:
    SimpleFile( const char* path ) : m_path( path )
    {
        std::ifstream stream( path, std::ios::binary | std::ios::ate );
        m_size = stream.tellg();
        stream.seekg( 0, std::ios::beg );
        m_content = new std::uint8_t[m_size];
        stream.read( static_cast<char*>( m_content ), m_size );
    }

    const char* getPath() const
    {
        return m_path.c_str();
    }

    void* getContent() const
    {
        return m_content;
    }

    std::uint64_t getSize() const
    {
        return m_size;
    }

protected:
private:
    void* m_content{ nullptr };
    std::uint64_t m_size{ 0u };
    std::string m_path;
};


void PakFilesTests::SetUp()
{
    // Setup code for each test case
    m_simpleFile = std::make_unique<SimpleFile>( "Info.txt" );
}

PakFilesTests::PakFilesTests()
{
    // Constructor code
}

void PakFilesTests::SetUpTestCase()
{
    // Setup code for the entire test case
}

void PakFilesTests::createTestArchive( const char* archivePath )
{
    CUL::SFile file;
    file.Path = m_simpleFile->getPath();
    file.PathSize = file.Path.getSTDString().size() * sizeof( char );
    file.Content = m_simpleFile->getContent();
    file.FileSize = m_simpleFile->getSize();

    CUL::CULInterface::createInstance()->getFS()->deleteFile( archivePath );
    CUL::SFArchiveMetadata meta;
    meta.Path = archivePath;
    meta.FilesCount = 1u;
    meta.Files.push_back( file );

    CUL::Archiver::getInstance().createArchive( meta, CUL::EAccesMode::Write );
}

TEST_F( PakFilesTests, basicPakFileWrite )
{
    createTestArchive( "TestArchive.pak" );
}

TEST_F( PakFilesTests, basicPakFileLoad )
{
    createTestArchive( "TestArchive.pak" );
    CUL::IArchive& archive = CUL::Archiver::getInstance().readArchive( "TestArchive.pak" );
    CUL::SFile* file =  archive.getFile(m_simpleFile->getPath());

    ASSERT_EQ( file->FileSize, m_simpleFile->getSize() );
    const int result = std::memcmp( file->Content, m_simpleFile->getContent(), m_simpleFile->getSize() );
    ASSERT_EQ( result, 0 );
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