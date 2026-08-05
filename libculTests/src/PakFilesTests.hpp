#pragma once

#include "Gtest.hpp"

class PakFilesTests: public ::testing::Test
{
public:
protected:
    PakFilesTests();

    static void SetUpTestCase();
    void SetUp() override;

    void TearDown() override;
    static void TearDownTestCase();
    void createTestArchive();

    ~PakFilesTests();

private:
    
};
