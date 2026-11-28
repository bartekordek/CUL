#include "CUL/Network/Message.hpp"
#include "gtest/gtest.h"

TEST( NetworkMessageTests, HelloRoundTrip )
{
    const auto frame = Network::encode( Network::makeHello( "abc123" ) );
    ASSERT_EQ( frame.size(), Network::kHeaderSize + 6u );

    // Wire layout: "CUL1", version, type, big-endian length.
    EXPECT_EQ( frame[0], 'C' );
    EXPECT_EQ( frame[1], 'U' );
    EXPECT_EQ( frame[2], 'L' );
    EXPECT_EQ( frame[3], '1' );
    EXPECT_EQ( frame[4], Network::kProtocolVersion );
    EXPECT_EQ( frame[5], static_cast<std::uint8_t>( Network::MsgType::Hello ) );
    EXPECT_EQ( frame[6], 0 );
    EXPECT_EQ( frame[7], 6 );

    Network::Message decoded;
    std::size_t consumed = 0;
    ASSERT_EQ( Network::decode( frame.data(), frame.size(), decoded, consumed ), Network::DecodeStatus::Ok );
    EXPECT_EQ( consumed, frame.size() );

    std::string id;
    ASSERT_TRUE( Network::parseHello( decoded, id ) );
    EXPECT_EQ( id, "abc123" );
}

TEST( NetworkMessageTests, NeedMoreData )
{
    const auto frame = Network::encode( Network::makeHello( "abc123" ) );
    Network::Message decoded;
    std::size_t consumed = 0;
    EXPECT_EQ( Network::decode( frame.data(), 3, decoded, consumed ), Network::DecodeStatus::NeedMoreData );
    EXPECT_EQ( Network::decode( frame.data(), frame.size() - 1, decoded, consumed ),
               Network::DecodeStatus::NeedMoreData );
}

TEST( NetworkMessageTests, RejectsBadMagicVersionAndSize )
{
    auto frame = Network::encode( Network::makeHello( "abc123" ) );
    Network::MessageHeader header;

    auto bad = frame;
    bad[0] = 'X';
    EXPECT_EQ( Network::decodeHeader( bad.data(), bad.size(), header ), Network::DecodeStatus::BadMagic );

    bad = frame;
    bad[4] = 99;
    EXPECT_EQ( Network::decodeHeader( bad.data(), bad.size(), header ), Network::DecodeStatus::BadVersion );

    bad = frame;
    bad[6] = 0xFF;
    bad[7] = 0xFF;
    EXPECT_EQ( Network::decodeHeader( bad.data(), bad.size(), header ), Network::DecodeStatus::TooLarge );
}

TEST( NetworkMessageTests, ParseHelloRejectsOtherTypesAndEmpty )
{
    Network::Message m;
    std::string id;
    EXPECT_FALSE( Network::parseHello( m, id ) );  // Invalid type
    m.type = Network::MsgType::Hello;
    EXPECT_FALSE( Network::parseHello( m, id ) );  // empty payload
}

TEST( NetworkMessageTests, OversizedPayloadNotEncoded )
{
    Network::Message m;
    m.type = Network::MsgType::Hello;
    m.payload.resize( Network::kMaxPayloadSize + 1 );
    EXPECT_TRUE( Network::encode( m ).empty() );
}
