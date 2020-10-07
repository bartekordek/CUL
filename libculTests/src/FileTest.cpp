#include "FileTest.hpp"

#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/FileFactory.hpp"

void FileTest::SetUp()
{
    std::cout << "Current dir: " << CUL::FS::FSApi::getCurrentDir() << "\n";
}

TEST_F( FileTest, fileFileExtistFileReturnsTrue )
{
    std::unique_ptr<CUL::FS::IFile> file( CUL::FS::FileFactory::createRegularFileRawPtr( dummyFilePath ) );
    GTEST_ASSERT_EQ( true, file->exists() );
}

TEST_F( FileTest, fileFileDontExtistFileReturnsFalse )
{
    std::unique_ptr<CUL::FS::IFile> file( CUL::FS::FileFactory::createRegularFileRawPtr( "someNotExistingFile.exe" ) );
    GTEST_ASSERT_EQ( false, file->exists() );
}

TEST_F( FileTest, basicFileLoadFirstLine )
{
    std::unique_ptr<CUL::FS::IFile> file( CUL::FS::FileFactory::createRegularFileRawPtr( dummyFilePath ) );
    file->load();
    GTEST_ASSERT_EQ( "Line1", file->firstLine() );
}

TEST_F( FileTest, basicFileLoadlastLine )
{
    std::unique_ptr<CUL::FS::IFile> file( CUL::FS::FileFactory::createRegularFileRawPtr( dummyFilePath ) );
    file->load();
    GTEST_ASSERT_EQ( "Line3", file->lastLine() );
}

TEST_F( FileTest, loadCachedFileRegular )
{
    std::unique_ptr<CUL::FS::IFile> file( CUL::FS::FileFactory::createRegularFileRawPtr( dummyFilePath ) );
    file->load();
    auto text = file->getAsOneString();
    GTEST_ASSERT_NE( "", text );
}

TEST_F( FileTest, loadRawImage )
{
    auto f( CUL::FS::FileFactory::createRawImageRawPtr
( dummyImage ) );
    GTEST_ASSERT_NE( nullptr, f.get() );
    GTEST_ASSERT_NE( nullptr, f->getData() );

    const auto& size = f->getImageInfo().size;
    GTEST_ASSERT_EQ( 407, size.width );
    GTEST_ASSERT_EQ( 412, size.height );
}