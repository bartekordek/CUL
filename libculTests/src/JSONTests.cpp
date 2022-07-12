#include "JSONTests.hpp"
#include "CUL/Filesystem/FileFactory.hpp"
#include "CUL/JSON/INode.hpp"

using namespace CUL;
using JFilePtr = CUL::JSON::IJSONFile;
using JFile = std::unique_ptr<JFilePtr>;

CUL::GUTILS::DumbPtr<CUL::CULInterface> JSONTests::m_culInterface = nullptr;

JSONTests::JSONTests()
{
    jsonTestFileName = { "test.json" };
}

void JSONTests::SetUpTestCase()
{
    m_culInterface = CUL::CULInterface::createInstance();
}

void JSONTests::SetUp()
{
}

TEST_F( JSONTests, objectTypeIsCorrect )
{
    JSON::INode object;
    GTEST_ASSERT_EQ(
        JSON::ElementType::NONE == object.getType(),
        true );
}

TEST_F( JSONTests, addObject )
{
    JSON::INode object;
    JSON::INode* child = new JSON::INode();
    const String childName = "WAT";
    child->setName( childName );

    object.setValue( child );

    GTEST_ASSERT_EQ( childName == object.getObject()->getName(), true );
}

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable : 5045 )
#endif
TEST_F( JSONTests, nestData )
{
    JSON::INode node;
    JSON::ChildrenNodes nodes;
    const int size = 10;
    for( auto i = 0; i < size; ++i )
    {
        auto ptr = new JSON::INode();
        ptr->setValue( i );
        nodes.push_back( ptr );
    }
    node.setValue( nodes );
    GTEST_ASSERT_EQ( size == node.getArray().size(), true );
}
#if _MSC_VER
#pragma warning( pop )
#endif

TEST_F( JSONTests, arrayAddElements )
{
    JSON::INode node;
    JSON::ChildrenNodes nodes;
    auto val1 = new JSON::INode( "val1", "10" );
    auto val2 = new JSON::INode( "val2", "11" );
    auto val3 = new JSON::INode( "name", "some name" );
    nodes.push_back( val1 );
    nodes.push_back( val2 );
    nodes.push_back( val3 );
    node.setValue( nodes );
    GTEST_ASSERT_EQ( 3 == node.getArray().size(), true );
}

TEST_F( JSONTests, fileLoadTest )
{
    JFile jsonFilePtr( m_culInterface->getFF()->createJSONFileRawPtr( jsonTestFileName ) );
    GTEST_ASSERT_EQ( true == jsonFilePtr->exists(), true );
    jsonFilePtr->load();
}

TEST_F( JSONTests, getRootElement )
{
    JFile jsonFilePtr( m_culInterface->getFF()->createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load();
    auto rootElement = jsonFilePtr->getRoot();
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::ARRAY == rootElement->getType(), true );
    GTEST_ASSERT_EQ( CUL::String( "root" ) == rootElement->getName(), true );
}

TEST_F( JSONTests, findProperty )
{
    JFile jsonFilePtr( m_culInterface->getFF()->createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load();
    auto rootElement = jsonFilePtr->getRoot();

    auto age = rootElement->findChild( "age" );
    GTEST_ASSERT_NE( nullptr == age, true );
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::INT == age->getType(), true );
    GTEST_ASSERT_EQ( 99 == age->getInt(), true );
}

TEST_F( JSONTests, arraySize )
{
    JFile jsonFilePtr( m_culInterface->getFF()->createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load();
    auto rootElement = jsonFilePtr->getRoot();
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::ARRAY == rootElement->getType(), true );
    GTEST_ASSERT_EQ( CUL::String( "root" ) == rootElement->getName(), true );

    auto messages = rootElement->findChild( "messages" );
    GTEST_ASSERT_EQ( nullptr == messages, false );

    GTEST_ASSERT_EQ( CUL::JSON::ElementType::ARRAY == messages->getType(), true );
    GTEST_ASSERT_EQ( 3 == messages->getArray().size(), true );
}

TEST_F( JSONTests, arrayCorrectness )
{
    JFile jsonFilePtr( m_culInterface->getFF()->createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load();
    auto rootElement = jsonFilePtr->getRoot();
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::ARRAY == rootElement->getType(), true );
    GTEST_ASSERT_EQ( CUL::String( "root" ) == rootElement->getName(), true );

    auto messages = rootElement->findChild( "messages" );
    GTEST_ASSERT_EQ( nullptr == messages, false );

    GTEST_ASSERT_EQ( CUL::JSON::ElementType::ARRAY == messages->getType(), true );
    GTEST_ASSERT_EQ( 3 == messages->getArray().size(), true );
}


void JSONTests::TearDown()
{
}

void JSONTests::TearDownTestCase()
{
    m_culInterface.release();
}


JSONTests::~JSONTests()
{
}