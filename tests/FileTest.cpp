#include "FileTest.hpp"

#include "CUL/IFile.hpp"

TEST_F( FileTest, basicFileLoadFirstLine )
{
	auto f = CUL::FS::IFile::createFile( dummyFilePath );
	f->load();
	GTEST_ASSERT_EQ( "Line1", f->firstLine()->getVal() );
}

TEST_F( FileTest, basicFileLoadlastLine )
{
	auto f = CUL::FS::IFile::createFile( dummyFilePath );
	f->load();
	GTEST_ASSERT_EQ( "Line3", f->lastLine()->getVal() );
}

TEST_F( FileTest, existence )
{
	auto f = CUL::FS::IFile::createFile( dummyFilePath );
	GTEST_ASSERT_EQ( true, f->exists() );
}