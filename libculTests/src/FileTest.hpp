#pragma once

#include "Gtest.hpp"
#include "CUL/CULInterface.hpp"
#include "CUL/GenericUtils/DumbPtr.hpp"

#if _MSC_VER
#pragma warning( push )
#pragma warning( disable: 4625 )
#pragma warning( disable: 4626 )
#endif
class FileTest: public ::testing::Test
{
public:
protected:
    FileTest();

    static void SetUpTestCase();
    void SetUp() override;

    void TearDown() override;
    static void TearDownTestCase();

    CUL::String dummyFilePath = "../media/Dummy.txt";
    CUL::String dummyImage = "../media/pikaczu.png";

    static CUL::GUTILS::DumbPtr<CUL::CULInterface> m_culInterface;
    static CUL::FS::FSApi* m_fsApi;

    ~FileTest();
};

#ifdef _MSC_VER
#pragma warning( pop )
#endif