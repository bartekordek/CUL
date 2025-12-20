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

// TODO: Re-enable tests.
/*
TEST_F( JSONTests, configTestOneFieldRapid )
{
    auto file = ConfigFile::createFile( EParserType::Rapidjson );
    file->loadFile( jsonTestFileName.string() );
    const ConfigNode* ageValue = file->getValue( { std::string( "age" ) } );
    GTEST_ASSERT_EQ( std::get<std::int32_t>( ageValue->Value ), 99 );
}

TEST_F( JSONTests, configTestTwoFieldRapid )
{
    auto file = ConfigFile::createFile( EParserType::Rapidjson );
    file->loadFile( jsonTestFileName.string() );
    const auto value = file->getValue( { std::string( "objs" ), std::string( "0" ), std::string( "variable" ) } );
    GTEST_ASSERT_EQ( std::get<std::string>( value->Value ), "value" );
}

TEST_F( JSONTests, configTestOneFieldJsonxx )
{
    auto file = ConfigFile::createFile( EParserType::Jsonxx );
    file->loadFile( jsonTestFileName.string() );
    const ConfigNode* ageValue = file->getValue( { std::string( "age" ) } );
    const double floatVal = std::get<double>( ageValue->Value );
    const std::int32_t intVal = static_cast<std::int32_t>( floatVal );
    GTEST_ASSERT_EQ( intVal, 99 );
}

TEST_F( JSONTests, configTestTwoFieldJsonxx )
{
    //auto file = ConfigFile::createFile( EParserType::Jsonxx );
    //file->loadFile( jsonTestFileName.string() );
    //const auto value = file->getValue( { std::string( "objs" ), std::string( "0" ), std::string( "variable" ) } );
    //GTEST_ASSERT_EQ( std::get<std::string>( value->Value ), "value" );
}

#define TEST_WRITE 1
TEST_F( JSONTests, configJSONWRITETEST )
{
    auto file = ConfigFile::createFile( EParserType::Jsonxx );
    file->loadFile( jsonTestFileName.string() );
    ConfigNode cn;
    cn.Value = "msg 4";
    cn.Type = EVarType::String;
    file->addOverwriteValue( cn, { std::string( "messages" ) } );
    file->saveFile( "testwrite.json" );

    auto newFile = ConfigFile::createFile( EParserType::Jsonxx );
    newFile->loadFile( "testwrite.json" );
    const auto value = newFile->getValue( { std::string( "messages" ), std::string( "3" ) } );
    GTEST_ASSERT_TRUE( std::get<std::string>( cn.Value ) == std::get<std::string>( value->Value ), "String should be the same." );
}

*/
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
    jsonFilePtr->load( true, false );
}

TEST_F( JSONTests, getRootElement )
{
    JFile jsonFilePtr( m_culInterface->getFF()->createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load( true, false );
    auto rootElement = jsonFilePtr->getRoot();
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::ARRAY == rootElement->getType(), true );
    GTEST_ASSERT_EQ( CUL::String( "root" ) == rootElement->getName(), true );
}

TEST_F( JSONTests, findProperty )
{
    JFile jsonFilePtr( m_culInterface->getFF()->createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load( true, false );
    auto rootElement = jsonFilePtr->getRoot();

    auto age = rootElement->findChild( "age" );
    GTEST_ASSERT_NE( nullptr == age, true );
    GTEST_ASSERT_EQ( CUL::JSON::ElementType::INT == age->getType(), true );
    GTEST_ASSERT_EQ( 99 == age->getInt(), true );
}

TEST_F( JSONTests, arraySize )
{
    JFile jsonFilePtr( m_culInterface->getFF()->createJSONFileRawPtr( jsonTestFileName ) );
    jsonFilePtr->load( true, false );
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
    jsonFilePtr->load( true, false );
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
