#include "CSVFileTests.hpp"
#include "CUL/Filesystem/FileFactory.hpp"

using FF = CUL::FS::FileFactory;
using FilePtr = CUL::FS::IFile;
using CSVFilePtr = CUL::FS::ICSVFile;

CUL::GUTILS::DumbPtr<CUL::CULInterface> CSVFileTests::m_culInterface = nullptr;

CSVFileTests::CSVFileTests()
{
}

void CSVFileTests::SetUpTestCase()
{
    m_culInterface = CUL::CULInterface::createInstance();
}

void CSVFileTests::SetUp()
{
}

TEST_F( CSVFileTests, Load )
{
    std::unique_ptr<CSVFilePtr> filePtr( m_culInterface->getFF()->createCSVFileRawPtr( "../media/test.csv" ) );
    filePtr->setDelimeter( "," );
    filePtr->load( true, false );
    GTEST_ASSERT_GT( filePtr->getRowsCount(), 0 );
}

TEST_F( CSVFileTests, UnLoad )
{
    std::unique_ptr<CSVFilePtr> filePtr( m_culInterface->getFF()->createCSVFileRawPtr( "../media/test.csv" ) );
    filePtr->load( true, false );
    filePtr->unload();
    GTEST_ASSERT_EQ( filePtr->getRowsCount(), 0 );
}

TEST_F( CSVFileTests, ReadFirstVal )
{
    std::unique_ptr<CSVFilePtr> filePtr( m_culInterface->getFF()->createCSVFileRawPtr( "../media/test.csv" ) );
    filePtr->fileContainsQuotationMarks( false );
    filePtr->load( true, false );
    auto value = filePtr->getVal( 0, 0 );
    GTEST_ASSERT_EQ( value, "CSV_ISO_LANG" );
}

TEST_F( CSVFileTests, LineCount )
{
    std::unique_ptr<CSVFilePtr> filePtr( m_culInterface->getFF()->createCSVFileRawPtr( "../media/test.csv" ) );
    filePtr->load( true, false );
    auto rowCount = filePtr->getRowsCount();
    auto lineCount = filePtr->getLinesCount();
    GTEST_ASSERT_EQ( rowCount, lineCount );
}

void CSVFileTests::TearDown()
{
}

void CSVFileTests::TearDownTestCase()
{
    m_culInterface.release();
}

CSVFileTests::~CSVFileTests()
{
}
