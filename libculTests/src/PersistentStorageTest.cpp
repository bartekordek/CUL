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

TEST_F( PersistentDataJsonTests, readTest )
{
    CUL::PersistentDataJson data;
    data.init( CUL_STR( "writeTest" ) );

    data.addNode( CUL_STR( "root/child1" ), { CUL_STR( "boolValue" ), true } );

    const auto val = data.getValue( CUL_STR( "root/child1/boolValue" ) );
    ASSERT_TRUE( std::holds_alternative<bool>( val ) );
    ASSERT_TRUE( std::get<bool>( val ) == true );
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