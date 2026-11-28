#include "CUL/Network/Message.hpp"

namespace Network
{

namespace
{
void putU16( std::vector<std::uint8_t>& out, std::uint16_t v )
{
    out.push_back( static_cast<std::uint8_t>( ( v >> 8 ) & 0xFF ) );
    out.push_back( static_cast<std::uint8_t>( v & 0xFF ) );
}

void putU32( std::vector<std::uint8_t>& out, std::uint32_t v )
{
    out.push_back( static_cast<std::uint8_t>( ( v >> 24 ) & 0xFF ) );
    out.push_back( static_cast<std::uint8_t>( ( v >> 16 ) & 0xFF ) );
    out.push_back( static_cast<std::uint8_t>( ( v >> 8 ) & 0xFF ) );
    out.push_back( static_cast<std::uint8_t>( v & 0xFF ) );
}

std::uint16_t getU16( const std::uint8_t* p )
{
    return static_cast<std::uint16_t>( ( p[0] << 8 ) | p[1] );
}

std::uint32_t getU32( const std::uint8_t* p )
{
    return ( std::uint32_t( p[0] ) << 24 ) | ( std::uint32_t( p[1] ) << 16 ) |
           ( std::uint32_t( p[2] ) << 8 ) | std::uint32_t( p[3] );
}
}  // namespace

std::vector<std::uint8_t> encode( const Message& message )
{
    if( message.payload.size() > kMaxPayloadSize )
        return {};

    std::vector<std::uint8_t> out;
    out.reserve( kHeaderSize + message.payload.size() );
    putU32( out, kMagic );
    out.push_back( kProtocolVersion );
    out.push_back( static_cast<std::uint8_t>( message.type ) );
    putU16( out, static_cast<std::uint16_t>( message.payload.size() ) );
    out.insert( out.end(), message.payload.begin(), message.payload.end() );
    return out;
}

DecodeStatus decodeHeader( const std::uint8_t* data,
                           std::size_t size,
                           MessageHeader& outHeader )
{
    if( size < kHeaderSize )
        return DecodeStatus::NeedMoreData;
    if( getU32( data ) != kMagic )
        return DecodeStatus::BadMagic;
    if( data[4] != kProtocolVersion )
        return DecodeStatus::BadVersion;

    const std::uint16_t len = getU16( data + 6 );
    if( len > kMaxPayloadSize )
        return DecodeStatus::TooLarge;

    outHeader.type = static_cast<MsgType>( data[5] );
    outHeader.payloadLen = len;
    return DecodeStatus::Ok;
}

DecodeStatus decode( const std::uint8_t* data,
                     std::size_t size,
                     Message& outMessage,
                     std::size_t& consumed )
{
    consumed = 0;
    MessageHeader header;
    const auto status = decodeHeader( data, size, header );
    if( status != DecodeStatus::Ok )
        return status;

    const std::size_t total = kHeaderSize + header.payloadLen;
    if( size < total )
        return DecodeStatus::NeedMoreData;

    outMessage.type = header.type;
    outMessage.payload.assign( data + kHeaderSize, data + total );
    consumed = total;
    return DecodeStatus::Ok;
}

Message makeHello( const std::string& instanceId )
{
    Message m;
    m.type = MsgType::Hello;
    const auto len = instanceId.size() > kMaxInstanceIdSize ? kMaxInstanceIdSize : instanceId.size();
    m.payload.assign( instanceId.begin(), instanceId.begin() + static_cast<std::ptrdiff_t>( len ) );
    return m;
}

bool parseHello( const Message& message, std::string& outInstanceId )
{
    if( message.type != MsgType::Hello )
        return false;
    if( message.payload.empty() || message.payload.size() > kMaxInstanceIdSize )
        return false;
    outInstanceId.assign( message.payload.begin(), message.payload.end() );
    return true;
}

const char* toString( MsgType type )
{
    switch( type )
    {
        case MsgType::Hello:
            return "Hello";
        // EXTENSION: add names for new message types.
        default:
            return "Unknown";
    }
}

}  // namespace Network
