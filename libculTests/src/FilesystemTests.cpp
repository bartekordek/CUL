#include "FilesystemTests.hpp"
#include "CUL/Filesystem/Path.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/Log/ILogContainer.hpp"

using Path = CUL::FS::Path;

FilesystemTests::FilesystemTests()
{
    CUL::LOG::LOG_CONTAINER::getLogger()->log( "FilesystemTests::FilesystemTests()" );
    auto cwd = CUL::FS::FSApi::getCurrentDir();
    CUL::LOG::LOG_CONTAINER::getLogger()->log( "Current dir: " + cwd.string() );
}

TEST_F( FilesystemTests, GetExtension )
{
    Path file( "SomeDirectory/SomeFile.extension" );
    ASSERT_EQ( file.getExtension(), ".extension" );
}

TEST_F( FilesystemTests, GetDirectory )
{
    Path file( "SomeDirectory/SomeFile.extension" );
    ASSERT_EQ( file.getDir(), "SomeDirectory" );
}

TEST_F( FilesystemTests, GetBaseName )
{
    Path file( "SomeDirectory/SomeFile.extension" );
    ASSERT_EQ( file.getBaseName(), "SomeFile" );
}

TEST_F( FilesystemTests, GetFullPath )
{
    Path file( "C:\\SomeDirectory\\SomeFile.extension" );
    ASSERT_EQ( file.getPath(), "C:/SomeDirectory/SomeFile.extension" );
}

TEST_F( FilesystemTests, FileExistence )
{
    std::string filePath = "../media/Dummy.txt";
    CUL::LOG::LOG_CONTAINER::getLogger()->log( "Trying to find: " + filePath );
    Path file( filePath.c_str() );
    ASSERT_EQ( file.exists(), true );
}

TEST_F( FilesystemTests, FileNotExist )
{
    Path file( "C:/Windows/System32/xcopy312312.exe" );
    ASSERT_EQ( file.exists(), false );
}

TEST_F( FilesystemTests, listFilesCount )
{
    auto directory = CUL::FS::FSApi::getDirectory( "FSTEST" );
    ASSERT_EQ( 4, directory->getChildList().size() );
    delete directory;
}