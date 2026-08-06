#pragma once

#include "Gtest.hpp"
#include "CUL/STL_IMPORTS/STD_memory.hpp"

class SimpleFile;

class PakFilesTests: public ::testing::Test
{
public:
protected:
    PakFilesTests();

    static void SetUpTestCase();
    void SetUp() override;

    void TearDown() override;
    static void TearDownTestCase();
    void createTestArchive( const char* archivePath );

    const SimpleFile& getSimpleFile() const;

    std::unique_ptr<SimpleFile> m_simpleFile;

    ~PakFilesTests();

private:
    
};
