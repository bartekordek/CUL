#include "SphericalTests.hpp"
#include "CUL/Math/SphericalCoord.hpp"
#include "CUL/Math/Utils.hpp"

constexpr float epislon{ 0.0001f };

void SphericalTests::SetUpTestCase()
{
    constexpr std::size_t sizeOfWchar = sizeof( wchar_t );
    std::cout << "wchar_t size: " << sizeOfWchar << "\n";
}

void SphericalTests::TearDownTestCase()
{
}

TEST_F( SphericalTests, ConversionBasic )
{
    CUL::MATH::SphericalCoord<float> spherical;
    const float x = 1.f;
    const float y = 2.f;
    const float z = 3.f;

    float outX = -1.f;
    float outY = -1.f;
    float outZ = -1.f;

    spherical.fromCarthezian( x, y, z );
    spherical.toCarthezian( outX, outY, outZ );

    ASSERT_TRUE( CUL::MATH::Utils::equals( outX, x, epislon ) );
    ASSERT_TRUE( CUL::MATH::Utils::equals( outY, y, epislon ) );
    ASSERT_TRUE( CUL::MATH::Utils::equals( outZ, z, epislon ) );
}

TEST_F( SphericalTests, ConversionIncremental )
{
    //float y = 0.f;
    //for(float x = 1.f)
    //{
    //}
}