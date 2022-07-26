#include "UniquePtrOnStackTest.hpp"

#include "CUL/Memory/UniquePtrOnStack.hpp"

#include "CUL/STL_IMPORTS/STD_iostream.hpp"

static int gval = 0;

namespace UniquePtrOnStackTest
{
Base::Base()
{
    std::cout << "Base()" << this << "\n";
    ++gval;
}

Base::~Base()
{
    std::cout << "~Base()" << this << "\n";
    --gval;
}

Derived::Derived()
{
    std::cout << "Derived()" << this << "\n";
    ++gval;
}

Derived::~Derived()
{
    std::cout << "~Derived()" << this << "\n";
    --gval;
}

UniquePtrOnStack::UniquePtrOnStack()
{
}

UniquePtrOnStack::~UniquePtrOnStack()
{
}

void UniquePtrOnStack::SetUpTestCase()
{
}

void UniquePtrOnStack::TearDownTestCase()
{
}

TEST_F( UniquePtrOnStack, genericTest )
{
    {
        //auto ptr = CUL::Memory::makeUnique<Derived, sizeof( Derived )>();
        CUL::Memory::UniquePtrOnStack<Derived, sizeof( Derived )> ptr;
        ptr.create(
            [](void* memory)
            {
                return new( memory ) Derived();
            },
            [](Derived* ptr)
            {
                ptr->~Derived();
            } );
    }
    GTEST_ASSERT_EQ( 0, gval );
}

}  // namespace UniquePtrOnStackTest