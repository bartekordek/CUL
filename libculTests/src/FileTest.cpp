#include "FileTest.hpp"

#include "CUL/Filesystem/FileFactory.hpp"

TEST_F( FileTest, fileFileExtistFileReturnsTrue )
{
    auto f = CUL::FS::FileFactory::createRegularFileRawPtr( dummyFilePath );
    GTEST_ASSERT_EQ( true, f->exists() );
    delete f;
    f = nullptr;
}

TEST_F( FileTest, fileFileDontExtistFileReturnsFalse )
{
    auto f = CUL::FS::FileFactory::createRegularFileRawPtr( "someNotExistingFile.exe" );
    GTEST_ASSERT_EQ( false, f->exists() );
    delete f;
    f = nullptr;
}

TEST_F( FileTest, basicFileLoadFirstLine )
{
    auto f = CUL::FS::FileFactory::createRegularFileRawPtr( dummyFilePath );
    f->load();
    GTEST_ASSERT_EQ( "Line1", f->firstLine() );
    delete f;
    f = nullptr;
}

TEST_F( FileTest, basicFileLoadlastLine )
{
    auto f = CUL::FS::FileFactory::createRegularFileRawPtr( dummyFilePath );
    f->load();
    GTEST_ASSERT_EQ( "Line3", f->lastLine() );
    delete f;
    f = nullptr;
}

TEST_F( FileTest, loadCachedFileRegular )
{
    auto f = CUL::FS::FileFactory::createRegularFileRawPtr( dummyFilePath );
    f->load();
    auto text = f->getAsOneString();
    delete f;
    f = nullptr;
}

TEST_F( FileTest, loadRawImage )
{
    std::unique_ptr<CUL::Graphics::IRawImage> f( CUL::FS::FileFactory::createRawImageRawPtr( dummyImage ) );
    GTEST_ASSERT_NE( nullptr, f->getData() );

    const auto& fileSize = f->getSize();
    GTEST_ASSERT_EQ( 407, fileSize.getX() );
    GTEST_ASSERT_EQ( 412, fileSize.getY() );
}