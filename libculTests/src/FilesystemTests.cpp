#include "FilesystemTests.hpp"

#include "CUL/Filesystem/Path.hpp"
#include "CUL/Filesystem/FS.hpp"
#include "CUL/Filesystem/IFile.hpp"
#include "CUL/Filesystem/FSApi.hpp"

#include "CUL/STL_IMPORTS/STD_memory.hpp"

using Path = CUL::FS::Path;

CUL::GUTILS::DumbPtr<CUL::CULInterface> FilesystemTests::m_culInterface = nullptr;

FilesystemTests::FilesystemTests()
{
    m_culInterface->getLogger()->log( "FilesystemTests::FilesystemTests()" );
    auto cwd = m_culInterface->getFS()->getCurrentDir();
    m_culInterface->getLogger()->log( "Current dir: " + cwd.string() );
}

void FilesystemTests::SetUpTestCase()
{
    m_culInterface = CUL::CULInterface::createInstance();
}

void FilesystemTests::SetUp()
{
}

TEST_F( FilesystemTests, ModificationTime )
{
#define CUL_TODO 0
#if CUL_TODO  // Disabled because build github build machine modifies files.
    Path file( "FSTEST/Config.txt" );
    CUL::Time modTime;
    file.getLastModificationTime( modTime );
    const auto modTimeAsString = modTime.toString();
    CUL::LOG::ILogger::getInstance().logVariable( CUL::LOG::Severity::Info, "Mod time: %s", modTimeAsString.cStr() );

    ASSERT_TRUE( modTime.getYear() == 2025u );
    ASSERT_TRUE( modTime.getMonth() == 2u );
    ASSERT_TRUE( modTime.getDay() == 2u );

    ASSERT_TRUE( modTime.getHour() == 23u );
    ASSERT_TRUE( modTime.getMinute() == 50u );
    ASSERT_TRUE( modTime.getSecond() == 43u );
#endif  // #if defined(CUL_TODO)
}

TEST_F( FilesystemTests, GetExtension )
{
    Path file( "SomeDirectory/SomeFile.extension" );
    ASSERT_EQ( file.getExtension(), "extension" );
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
    m_culInterface->getLogger()->log( "Trying to find: " + filePath );
    Path file( filePath.c_str() );
    ASSERT_EQ( file.exists(), true );
}

TEST_F( FilesystemTests, TimeModified )
{
    std::string filePath = "../media/Dummy.txt";
    CUL::Time modificationTime;
    m_culInterface->getFS()->getLastModificationTime( filePath, modificationTime );
    auto modTime = modificationTime.toString();
    ASSERT_EQ( modTime.empty(), false );
}

TEST_F( FilesystemTests, FileNotExist )
{
    Path file( "C:/Windows/System32/xcopy312312.exe" );
    ASSERT_EQ( file.exists(), false );
}

TEST_F( FilesystemTests, listFilesCount )
{
    std::unique_ptr<CUL::FS::IFile> directory( m_culInterface->getFS()->getDirectory( "FSTEST" ) );
    ASSERT_EQ( 5, directory->getChildList().size() );
}

void FilesystemTests::TearDown()
{
}

void FilesystemTests::TearDownTestCase()
{
    m_culInterface.release();
}