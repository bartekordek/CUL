#include "ListTests.hpp"
#include "CUL/ListFactory.hpp"
#include "CUL/IIterator.hpp"
#include <memory>

unsigned noticableAmount = 10000 * 1000;

ListTests::ListTests( void )
{
}

ListTests::~ListTests()
{
}

void ListTests::SetUpTestCase()
{   
}

void ListTests::TearDownTestCase()
{
}

TEST_F( ListTests, VectorDoubleAdd )
{
    auto result = std::make_unique<CUL::IList<double>>( CUL::ListFactory::createVectorListPtr<double>() );
    result->pushBack( 2.2 );
    GTEST_ASSERT_EQ( 1, result->size() );
}
/*
TEST_F( ListTests, VectorIntIterateOneElement )
{
    auto result = std::make_unique<CUL::IList<unsigned>>( CUL::ListFactory::createVectorListPtr<unsigned>() );

    unsigned limit = 1;
    for( unsigned i = 0; i < limit; ++i )
    {
        result->pushBack( i );
    }

    unsigned i = 0;
    CUL::IIterator<unsigned>& iterator = result->getRandomIterator();
    GTEST_ASSERT_EQ( true, iterator.hasNext() );
    while( iterator.hasNext() )
    {
        GTEST_ASSERT_EQ( i, iterator.next() );
        ++i;
    }
}

TEST_F( ListTests, VectorIntIterateTwoElements )
{
    auto result = std::make_unique<CUL::IList<unsigned>>( CUL::ListFactory::createVectorListPtr<unsigned>() );

    unsigned limit = 4;
    for( unsigned i = 0; i < limit; ++i )
    {
        result->pushBack( i );
    }

    unsigned i = 0;
    auto& iterator = result->getRandomIterator();
    GTEST_ASSERT_EQ( true, iterator.hasNext() );
    while( iterator.hasNext() )
    {
         GTEST_ASSERT_EQ( i, iterator.next() );
        ++i;
    }
}

TEST_F( ListTests, VectorIntIterateManyElements )
{
    auto result = std::make_unique<CUL::IList<unsigned>>( CUL::ListFactory::createVectorListPtr<unsigned>() );

    unsigned limit = noticableAmount;
    for( unsigned i = 0; i < limit; ++i )
    {
        result->pushBack( i );
    }
    
    unsigned i = 0;
    auto& iterator = result->getRandomIterator();
    GTEST_ASSERT_EQ( true, iterator.hasNext() );
    while( iterator.hasNext() )
    {
        GTEST_ASSERT_EQ( i, iterator.next() );
        ++i;
    }
}

TEST_F( ListTests, LinkedDoubleAdd )
{
    auto result = std::make_unique<CUL::IList<double>>( CUL::ListFactory::createLinkedListPtr<double>() );

    result->pushBack( 2.2 );
    GTEST_ASSERT_EQ( 1, result->size() );
}

TEST_F( ListTests, LinkedIntIterateOneElement )
{
    auto result = std::make_unique<CUL::IList<unsigned>>( CUL::ListFactory::createLinkedListPtr<unsigned>() );

    unsigned limit = 1;
    for( unsigned i = 0; i < limit; ++i )
    {
        result->pushBack( i );
    }

    unsigned i = 0;
    auto& iterator = result->getRandomIterator();
    GTEST_ASSERT_EQ( true, iterator.hasNext() );
    while( iterator.hasNext() )
    {
        GTEST_ASSERT_EQ( i, iterator.next() );
        ++i;
    }
}

TEST_F( ListTests, LinkedIntIterateTwoElements )
{
    auto result = std::make_unique<CUL::IList<unsigned>>( CUL::ListFactory::createVectorListPtr<unsigned>() );

    unsigned limit = 4;
    for( unsigned i = 0; i < limit; ++i )
    {
        result->pushBack( i );
    }

    unsigned i = 0;
    auto& iterator = result->getRandomIterator();
    GTEST_ASSERT_EQ( true, iterator.hasNext() );
    while( iterator.hasNext() )
    {
        GTEST_ASSERT_EQ( i, iterator.next() );
        ++i;
    }
}

TEST_F( ListTests, LinkedIntIterateManyElements )
{
    auto result = std::make_unique<CUL::IList<unsigned>>( CUL::ListFactory::createVectorListPtr<unsigned>() );

    unsigned limit = noticableAmount;
    for( unsigned i = 0; i < limit; ++i )
    {
        result->pushBack( i );
    }

    unsigned i = 0;
    auto& iterator = result->getRandomIterator();
    GTEST_ASSERT_EQ( true, iterator.hasNext() );
    while( iterator.hasNext() )
    {
        GTEST_ASSERT_EQ( i, iterator.next() );
        ++i;
    }
}
*/