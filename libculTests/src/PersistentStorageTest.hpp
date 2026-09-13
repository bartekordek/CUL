#pragma once

#include "CUL/CULInterface.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

#include "Gtest.hpp"

class PersistentDataJsonTests: public ::testing::Test
{
protected:
    PersistentDataJsonTests();
    virtual ~PersistentDataJsonTests();

    static void SetUpTestCase();
    void SetUp() override;

    void TearDown() override;
    static void TearDownTestCase();
};
