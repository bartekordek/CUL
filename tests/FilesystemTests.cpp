#include "FilesystemTests.hpp"
#include "CUL/Path.hpp"
#include "CUL/FS.hpp"
#include "CUL/STD_iostream.hpp"

using Path = CUL::FS::Path;

FilesystemTests::FilesystemTests()
{
    auto cwd = CUL::FS::FSApi::getCurrentDir();
    std::cout << "Current dir: " << cwd << "\n";
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
    ASSERT_EQ( file.getPath(), "C:\\SomeDirectory\\SomeFile.extension" );
}

TEST_F( FilesystemTests, FileExistence )
{
    std::string filePath = "../media/Dummy.txt";
    std::cout << "Trying to find: " << filePath << std::endl;
    Path file( filePath.c_str() );
    ASSERT_EQ( file.exists(), true );
}

TEST_F( FilesystemTests, FileNotExist )
{
    Path file( "C:\\Windows\\System32\\xcopy312312.exe" );
    ASSERT_EQ( file.exists(), false );
}