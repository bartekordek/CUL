#include "CSVFileTests.hpp"
#include "CUL/FileFactory.hpp"

using FF = CUL::FS::FileFactory;
using FilePtr = CUL::FS::IFile;
using CSVFilePtr = CUL::FS::ICSVFile;

CSVFileTests::CSVFileTests( void )
{

}

CSVFileTests::~CSVFileTests( void )
{

}

void CSVFileTests::SetUpTestCase()
{
}

void CSVFileTests::TearDownTestCase()
{
}

TEST_F( CSVFileTests, Load )
{
    std::unique_ptr<CSVFilePtr> filePtr( FF::createCSVFile( "../media/test.csv" ) );
    filePtr->load();
    GTEST_ASSERT_GT( filePtr->rowsCount(), 0 );
}

TEST_F( CSVFileTests, UnLoad )
{
    std::unique_ptr<CSVFilePtr> filePtr( FF::createCSVFile( "../media/test.csv" ) );
    filePtr->load();
    filePtr->unload();
    GTEST_ASSERT_EQ( filePtr->rowsCount(), 0 );
}

TEST_F( CSVFileTests, ReadFirstVal )
{
    std::unique_ptr<CSVFilePtr> filePtr( FF::createCSVFile( "../media/test.csv" ) );
    filePtr->load();
    auto value = filePtr->getVal( 0, 0 );
    GTEST_ASSERT_EQ( value, "CSV_ISO_LANG" );
}

TEST_F( CSVFileTests, LineCount )
{
    std::unique_ptr<CSVFilePtr> filePtr( FF::createCSVFile( "../media/test.csv" ) );
    filePtr->load();
    auto rowCount = filePtr->rowsCount();
    auto lineCount = filePtr->getLinesCount();
    GTEST_ASSERT_EQ( rowCount, lineCount );
}