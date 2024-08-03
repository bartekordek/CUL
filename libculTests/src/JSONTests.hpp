#pragma once

#include "CUL/CULInterface.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

#include "Gtest.hpp"


#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class JSONTests: public ::testing::Test
{
protected:
    JSONTests();
    virtual ~JSONTests();

    static void SetUpTestCase();
    void SetUp() override;

    void TearDown() override;
    static void TearDownTestCase();

    static CUL::GUTILS::DumbPtr<CUL::CULInterface> m_culInterface;
    CUL::String jsonTestFileName{ "test.json" };
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif