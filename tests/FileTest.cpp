#include "FileTest.hpp"

#include "CUL/IFile.hpp"

TEST_F( FileTest, fileFileExtistFileReturnsTrue )
{
    auto f = CUL::FS::IFile::createRegularFile( dummyFilePath );
    GTEST_ASSERT_EQ( true, f->exists() );
}

TEST_F( FileTest, fileFileDontExtistFileReturnsFalse )
{
    auto f = CUL::FS::IFile::createRegularFile( std::string( "someNotExistingFile.exe" ) );
    GTEST_ASSERT_EQ(false, f->exists());
}

TEST_F( FileTest, basicFileLoadFirstLine )
{
    auto f = CUL::FS::IFile::createRegularFile( dummyFilePath );
    f->load();
    GTEST_ASSERT_EQ( "Line1", f->firstLine() );
}

TEST_F( FileTest, basicFileLoadlastLine )
{
    auto f = CUL::FS::IFile::createRegularFile( dummyFilePath );
    f->load();
    GTEST_ASSERT_EQ( "Line3", f->lastLine() );
}

TEST_F( FileTest, loadCachedFileRegular )
{
    auto f = CUL::FS::IFile::createRegularFile( dummyFilePath );
    f->load();
    auto text = f->getAsOneString();
}