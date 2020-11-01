#pragma once

#include "CUL/CULInterface.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

#include "Gtest.hpp"

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif

class CSVFileTests: public ::testing::Test
{
protected:
    CSVFileTests();
    virtual ~CSVFileTests();

    static void SetUpTestCase();
    void SetUp() override;

    void TearDown() override;
    static void TearDownTestCase();

    static CUL::GUTILS::DumbPtr<CUL::CULInterface> m_culInterface;
};
#ifdef _MSC_VER
#pragma warning( pop )
#endif