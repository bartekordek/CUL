#include "CSVFileTests.hpp"
#include "CUL/FileFactory.hpp"

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
    auto file = CUL::FS::FileFactory::createCSVFile( "../media/test.csv" );
    file->load();
    GTEST_ASSERT_GT(  file->rowsCount(), 0 );
}

TEST_F( CSVFileTests, UnLoad )
{
    auto file = CUL::FS::FileFactory::createCSVFile( "../media/test.csv" );
    file->load();
    file->unload();
    GTEST_ASSERT_EQ( file->rowsCount(), 0 );
}

TEST_F( CSVFileTests, ReadFirstVal )
{
    auto file = CUL::FS::FileFactory::createCSVFile( "../media/test.csv" );
    file->load();
    auto value = file->getVal( 0, 0 );
    GTEST_ASSERT_EQ( value, "CSV_ISO_LANG" );
}

TEST_F( CSVFileTests, LineCount )
{
    auto file = CUL::FS::FileFactory::createCSVFile( "../media/test.csv" );
    file->load();
    auto rowCount = file->rowsCount();
    auto lineCount = file->getLinesCount();
    GTEST_ASSERT_EQ( rowCount, lineCount );
}