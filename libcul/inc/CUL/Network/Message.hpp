#pragma once

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "CUL/CUL.hpp"

// Minimal binary framing used on the TCP data channel between CUL peers.
//
// Wire format (all multi-byte integers are NETWORK byte order / big-endian):
//
//   offset size field
//   0      4    magic       0x43554C31  ("CUL1" when read as ASCII bytes)
//   4      1    version     kProtocolVersion (currently 1)
//   5      1    type        MsgType
//   6      2    payloadLen  number of payload bytes that follow (<= kMaxPayloadSize)
//   8      N    payload     type specific
//
// Hello payload: the sender's instance id as raw ASCII/UTF-8 bytes (no terminator).
//
// EXTENSION: bump kProtocolVersion for incompatible header changes. Receivers must
// reject versions they do not understand (see DecodeStatus::BadVersion).

namespace Network
{

constexpr std::uint32_t kMagic = 0x43554C31u;
constexpr std::uint8_t kProtocolVersion = 1;
constexpr std::size_t kHeaderSize = 8;
constexpr std::size_t kMaxPayloadSize = 1024;  // EXTENSION: raise / chunk for Data messages
constexpr std::size_t kMaxInstanceIdSize = 64;

// EXTENSION: add new message types here (Ping, Pong, Data, Goodbye, ...).
// Keep values stable - they are part of the wire format. 0 is reserved/invalid.
enum class MsgType : std::uint8_t
{
    Invalid = 0,
    Hello = 1,
    // Ping = 2,
    // Data = 3,
};

struct Message
{
    MsgType type = MsgType::Invalid;
    std::vector<std::uint8_t> payload;
};

struct MessageHeader
{
    MsgType type = MsgType::Invalid;
    std::uint16_t payloadLen = 0;
};

enum class DecodeStatus
{
    Ok,
    NeedMoreData,  // buffer too short, read more bytes and retry
    BadMagic,
    BadVersion,
    TooLarge  // payloadLen above kMaxPayloadSize
};

// Serialises a message into a single frame. Returns an empty vector if the payload
// is larger than kMaxPayloadSize.
CULLib_API std::vector<std::uint8_t> encode( const Message& message );

// Parses only the fixed 8 byte header (useful for stream reads: read header, then
// read payloadLen bytes).
CULLib_API DecodeStatus decodeHeader( const std::uint8_t* data,
                                      std::size_t size,
                                      MessageHeader& outHeader );

// Parses a full frame. On Ok `consumed` is the number of bytes used from `data`.
CULLib_API DecodeStatus decode( const std::uint8_t* data,
                                std::size_t size,
                                Message& outMessage,
                                std::size_t& consumed );

// Hello helpers.
CULLib_API Message makeHello( const std::string& instanceId );
// Returns false if message is not a valid Hello. EXTENSION: add more fields
// (tcp port, capabilities, name) to the Hello payload and bump the version.
CULLib_API bool parseHello( const Message& message, std::string& outInstanceId );

CULLib_API const char* toString( MsgType type );

}  // namespace Network
