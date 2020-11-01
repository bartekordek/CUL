#pragma once

#include "CUL/CULInterface.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

#include "Gtest.hpp"

class OSUtilsTests:
    public testing::Test
{
protected:
    OSUtilsTests();
    virtual ~OSUtilsTests();


    static void SetUpTestCase();
    void SetUp() override;

    void TearDown() override;
    static void TearDownTestCase();

    static CUL::GUTILS::DumbPtr<CUL::CULInterface> m_culInterface;

private:
    OSUtilsTests( const OSUtilsTests& val ) = delete;
    OSUtilsTests( OSUtilsTests&& val ) = delete;
    OSUtilsTests& operator=( const OSUtilsTests& rhv ) = delete;
};