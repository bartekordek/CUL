#include "PersistentStorageTest.hpp"
#include <CUL/Data/PersistentDataJson.hpp>

PersistentDataJsonTests::PersistentDataJsonTests()
{
}

void PersistentDataJsonTests::SetUpTestCase()
{
}

void PersistentDataJsonTests::SetUp()
{
}

TEST_F( PersistentDataJsonTests, writeTest )
{
    CUL::PersistentDataJson data;
    data.init( CUL_STR( "writeTest" ) );

    data.addNode( CUL_STR( "root/child1" ), { CUL_STR( "boolValue" ), true } );
    data.writeToFile();
}

void PersistentDataJsonTests::TearDownTestCase()
{
}

void PersistentDataJsonTests::TearDown()
{
}

PersistentDataJsonTests::~PersistentDataJsonTests()
{

}