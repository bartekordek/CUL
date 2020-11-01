#include "FileTest.hpp"

#include "CUL/Log/ILogger.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/FileFactory.hpp"

CUL::GUTILS::DumbPtr<CUL::CULInterface> FileTest::m_culInterface = nullptr;
CUL::FS::FSApi* FileTest::m_fsApi = nullptr;

void FileTest::SetUp()
{
    m_culInterface->getLogger()->log( "FileTest::SetUp()" );
    m_culInterface->getLogger()->log( "Current dir: " + m_fsApi->getCurrentDir() );
}

FileTest::FileTest()
{
    m_culInterface->getLogger()->log( "FileTest::FileTest()" );
}

void FileTest::SetUpTestCase()
{
    m_culInterface = CUL::CULInterface::createInstance();
    m_culInterface->getLogger()->log( "FileTest::SetUpTestCase()" );
    m_fsApi = m_culInterface->getFS();
}

TEST_F( FileTest, fileFileExtistFileReturnsTrue )
{
    std::unique_ptr<CUL::FS::IFile> file( m_culInterface->getFF()->createRegularFileRawPtr( dummyFilePath ) );
    GTEST_ASSERT_EQ( true, file->exists() );
}

TEST_F( FileTest, fileFileDontExtistFileReturnsFalse )
{
    std::unique_ptr<CUL::FS::IFile> file( m_culInterface->getFF()->createRegularFileRawPtr( "someNotExistingFile.exe" ) );
    GTEST_ASSERT_EQ( false, file->exists() );
}

TEST_F( FileTest, basicFileLoadFirstLine )
{
    std::unique_ptr<CUL::FS::IFile> file( m_culInterface->getFF()->createRegularFileRawPtr( dummyFilePath ) );
    file->load();
    auto firstLine = file->firstLine();
    auto asCstring = firstLine.cStr();
    GTEST_ASSERT_EQ( CUL::String( "Line1" ), asCstring );
}

TEST_F( FileTest, basicFileLoadlastLine )
{
    std::unique_ptr<CUL::FS::IFile> file( m_culInterface->getFF()->createRegularFileRawPtr( dummyFilePath ) );
    file->load();
    GTEST_ASSERT_EQ( CUL::String( "Line3" ), file->lastLine().cStr() );
}

TEST_F( FileTest, loadCachedFileRegular )
{
    std::unique_ptr<CUL::FS::IFile> file( m_culInterface->getFF()->createRegularFileRawPtr( dummyFilePath ) );
    file->load();
    auto text = file->getAsOneString().cStr();
    GTEST_ASSERT_NE( CUL::String( "" ), text );
}

TEST_F( FileTest, loadRawImage )
{
    auto f( m_culInterface->getFF()->createRawImageRawPtr
( dummyImage ) );
    GTEST_ASSERT_NE( nullptr, f.get() );
    GTEST_ASSERT_NE( nullptr, f->getData() );

    const auto& size = f->getImageInfo().size;
    GTEST_ASSERT_EQ( 407, size.width );
    GTEST_ASSERT_EQ( 412, size.height );
}

void FileTest::TearDown()
{
    m_culInterface->getLogger()->log( "FileTest::TearDown()" );
}

void FileTest::TearDownTestCase()
{
    m_culInterface->getLogger()->log( "FileTest::TearDownTestCase()" );
    m_culInterface.release();
}

FileTest::~FileTest()
{
    m_culInterface->getLogger()->log( "FileTest::~FileTest()" );
}