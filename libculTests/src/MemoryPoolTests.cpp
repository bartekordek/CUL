#include "MemoryPoolTests.hpp"

#include "CUL/Memory/MemoryPool.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"

using namespace CUL;
using namespace Memory;

MemoryPoolTests::MemoryPoolTests()
{
}

TEST_F( MemoryPoolTests, TEST_SINGLE_ALLOCATION )
{

    //CUL::Memory::MemoryPool mp;
    //{
    //    GUTILS::DumbPtr<TestClass<1>> dPtr;
    //    void* ptr = mp.getMemory( sizeof( TestClass<1> ) );
    //    TestClass<1>* tc = new( ptr ) TestClass<1>();
    //    dPtr = tc;
    //    dPtr.setMemoryPool( &mp );
    //    std::cout << "END?\n";
    //}
    //std::cout << "END?\n";
}

TEST_F( MemoryPoolTests, TEST_MULTIPLE_ALLOCATION )
{
    //CUL::Memory::MemoryPool mp;
    //{
    //    void* ptr1 = mp.getMemory( sizeof( TestClass<1> ) );
    //    GUTILS::DumbPtr<TestClass<1>> tc1 = new( ptr1 ) TestClass<1>();
    //    tc1.setMemoryPool( &mp );

    //    void* ptr2 = mp.getMemory( sizeof( TestClass<2> ) );
    //    GUTILS::DumbPtr<TestClass<2>> tc2 = new( ptr2 ) TestClass<2>();
    //    tc2.setMemoryPool( &mp );

    //    void* ptr3 = mp.getMemory( sizeof( TestClass<3> ) );
    //    GUTILS::DumbPtr<TestClass<3>> tc3 = new( ptr3 ) TestClass<3>();
    //    tc3.setMemoryPool( &mp );

    //    tc2.reset(nullptr);

    //    void* ptr4 = mp.getMemory( sizeof( TestClass<3> ) );
    //    GUTILS::DumbPtr<TestClass<3>> tc4 = new( ptr4 ) TestClass<3>();
    //    tc4.setMemoryPool( &mp );

    //    void* ptr5 = mp.getMemory( sizeof( TestClass<2> ) );
    //    GUTILS::DumbPtr<TestClass<2>> tc5 = new( ptr5 ) TestClass<2>();
    //    tc5.setMemoryPool( &mp );

    //}
}