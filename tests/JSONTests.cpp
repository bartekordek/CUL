#include "JSONTests.hpp"
#include "CUL/FileFactory.hpp"
#include "CUL/JSON/Object.hpp"
#include "CUL/JSON/DataPair.hpp"
#include "CUL/JSON/Array.hpp"

using namespace CUL;
using JFIlePtr = CUL::JSON::IJSONFile;

JSONTests::JSONTests( void )
{

}

JSONTests::~JSONTests( void )
{

}

void JSONTests::SetUpTestCase()
{
}

void JSONTests::TearDownTestCase()
{
}

TEST_F( JSONTests, objectTypeIsCorrect )
{
    JSON::Object object;
    GTEST_ASSERT_EQ( 
        JSON::ElementType::OBJECT,
        object.getType() );
}

TEST_F( JSONTests, addObject )
{
    JSON::Object object;
    JSON::Object* child = new JSON::Object();

    object.addChild( child );

    GTEST_ASSERT_EQ(
        1,
        object.getChildren().size() );
}

TEST_F( JSONTests, getSetDataPair )
{
    JSON::DataPair dataPair;
    MyString val( "some val" );
    dataPair.setVal( val );
    GTEST_ASSERT_EQ( val, dataPair.getVal() );
}

TEST_F( JSONTests, nestDataPairInObject )
{
    JSON::Object object;
    auto child = new JSON::DataPair();
    object.addChild( child );
    MyString val( "some val" );
    child->setVal( val );
    GTEST_ASSERT_EQ(
        1,
        object.getChildren().size() );
    auto& node = object.getChildren().front();
    GTEST_ASSERT_EQ( JSON::ElementType::VALUE, node->getType() );
    auto dp = static_cast<JSON::DataPair*>( node );
    GTEST_ASSERT_EQ( val, dp->getVal() );
}

TEST_F( JSONTests, arrayAddElements )
{
    JSON::Array arrayObj;
    auto val1 = new JSON::DataPair( "val1", "10" );
    auto val2 = new JSON::DataPair( "val2", "11" );
    auto val3 = new JSON::DataPair( "name", "some name" );
    arrayObj.addValue( val1 );
    arrayObj.addValue( val2 );
    arrayObj.addValue( val3 );
    GTEST_ASSERT_EQ( 3, arrayObj.getAllValues().size() );
}

TEST_F( JSONTests, arrayFindValue )
{
    JSON::Array arrayObj;
    auto val1 = new JSON::DataPair( "val1", "10" );
    auto val2 = new JSON::DataPair( "val2", "11" );
    auto val3 = new JSON::DataPair( "name", "some name" );
    arrayObj.addValue( val1 );
    arrayObj.addValue( val2 );
    arrayObj.addValue( val3 );

    auto foundedValue = arrayObj.getValue( "val1" );

    GTEST_ASSERT_NE( nullptr, foundedValue );
}

TEST_F( JSONTests, arrayFindValueCorrectness )
{
    JSON::Array arrayObj;
    auto val1 = new JSON::DataPair( "val1", "10" );
    auto val2 = new JSON::DataPair( "val2", "11" );
    auto val3 = new JSON::DataPair( "name", "some name" );
    arrayObj.addValue( val1 );
    arrayObj.addValue( val2 );
    arrayObj.addValue( val3 );

    auto foundedValue = static_cast<const JSON::DataPair*>( arrayObj.getValue( "val1" ) );

    GTEST_ASSERT_EQ( "10", foundedValue->getVal() );
}

TEST_F( JSONTests, fileLoadTest )
{
    std::unique_ptr<JFIlePtr> jsonFilePtr( CUL::FS::FileFactory::createJSONFileRawPtr( jsonTestFileName ) );
    GTEST_ASSERT_EQ( true, jsonFilePtr->exists() );
    jsonFilePtr->load();
}

TEST_F( JSONTests, getRootElement )
{
    std::unique_ptr<JFIlePtr> jsonFilePtr( CUL::FS::FileFactory::createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load();
    auto rootElement = jsonFilePtr->getRoot();
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::OBJECT, rootElement->getType() );
    GTEST_ASSERT_EQ( "root", rootElement->getName() );
}

TEST_F( JSONTests, findProperty )
{
    std::unique_ptr<JFIlePtr> jsonFilePtr( CUL::FS::FileFactory::createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load();
    auto rootElement = jsonFilePtr->getRoot();
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::OBJECT, rootElement->getType() );
    GTEST_ASSERT_EQ( "root", rootElement->getName() );

    auto age = rootElement->getChild( "age" );
    GTEST_ASSERT_NE( nullptr, age );

    GTEST_ASSERT_EQ( CUL::JSON::ElementType::VALUE, age->getType() );
    auto dp = static_cast< const CUL::JSON::DataPair* >( age );
    GTEST_ASSERT_EQ( "99", dp->getVal() );
}

TEST_F( JSONTests, arraySize )
{
    std::unique_ptr<JFIlePtr> jsonFilePtr( CUL::FS::FileFactory::createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load();
    auto rootElement = jsonFilePtr->getRoot();
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::OBJECT, rootElement->getType() );
    GTEST_ASSERT_EQ( "root", rootElement->getName() );

    auto messages = rootElement->getChild( "messages" );
    GTEST_ASSERT_NE( nullptr, messages );

    GTEST_ASSERT_EQ( CUL::JSON::ElementType::ARRAY, messages->getType() );
    auto array = static_cast< const CUL::JSON::Array* >( messages );
    GTEST_ASSERT_EQ( 3, array->getAllValues().size() );
}

TEST_F( JSONTests, arrayCorrectness )
{
    std::unique_ptr<JFIlePtr> jsonFilePtr( CUL::FS::FileFactory::createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load();
    auto rootElement = jsonFilePtr->getRoot();
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::OBJECT, rootElement->getType() );
    GTEST_ASSERT_EQ( "root", rootElement->getName() );

    auto messages = rootElement->getChild( "messages" );
    GTEST_ASSERT_NE( nullptr, messages );

    GTEST_ASSERT_EQ( CUL::JSON::ElementType::ARRAY, messages->getType() );
    auto array = static_cast< const CUL::JSON::Array* >( messages );
    GTEST_ASSERT_EQ( 3, array->getAllValues().size() );

    unsigned int i = 1;
    for( const auto& msg: array->getChildren() )
    {
        GTEST_ASSERT_EQ( CUL::JSON::ElementType::VALUE, msg->getType() );
        auto dp = static_cast< const CUL::JSON::DataPair* >( msg );
        auto testVal = CUL::MyString( "msg " ) + i++;
        auto& actualVal = dp->getVal();
        GTEST_ASSERT_EQ( testVal, actualVal );
    }
}