#include "FileTest.hpp"

#include "CUL/FileFactory.hpp"

TEST_F( FileTest, fileFileExtistFileReturnsTrue )
{
    auto f = CUL::FS::FileFactory::createRegularFile( dummyFilePath );
    GTEST_ASSERT_EQ( true, f->exists() );
    delete f;
    f = nullptr;
}

TEST_F( FileTest, fileFileDontExtistFileReturnsFalse )
{
    auto f = CUL::FS::FileFactory::createRegularFile( "someNotExistingFile.exe" );
    GTEST_ASSERT_EQ(false, f->exists());
    delete f;
    f = nullptr;
}

TEST_F( FileTest, basicFileLoadFirstLine )
{
    auto f = CUL::FS::FileFactory::createRegularFile( dummyFilePath );
    f->load();
    GTEST_ASSERT_EQ( "Line1", f->firstLine() );
    delete f;
    f = nullptr;
}

TEST_F( FileTest, basicFileLoadlastLine )
{
    auto f = CUL::FS::FileFactory::createRegularFile( dummyFilePath );
    f->load();
    GTEST_ASSERT_EQ( "Line3", f->lastLine() );
    delete f;
    f = nullptr;
}

TEST_F( FileTest, loadCachedFileRegular )
{
    auto f = CUL::FS::FileFactory::createRegularFile( dummyFilePath );
    f->load();
    auto text = f->getAsOneString();
    delete f;
    f = nullptr;
}
