#pragma once

#include "gtest/gtest.h"

class FilesystemTests: public ::testing::Test
{
protected:
    FilesystemTests();

    virtual ~FilesystemTests()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};