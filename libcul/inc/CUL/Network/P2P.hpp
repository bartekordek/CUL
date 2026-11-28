#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "CUL/CUL.hpp"

namespace Network
{

struct PeerInfo
{
    std::string address;  // dotted IPv4, e.g. "192.168.1.20"
    // TCP *data* port the peer listens on (taken from the discovery payload
    // "inst:<id>;tcp:<port>"; falls back to CUL::dataPortFor(instanceId) when the
    // peer did not announce one). NOT the UDP discovery port.
    std::uint16_t port = 0;
    std::string instanceId;
};

class P2P
{
public:
    // The same port and appId must be used by every instance of your app.
    CULLib_API explicit P2P( std::uint16_t port = 12021,
                             std::uint32_t appId = 0x4D415441 );
    CULLib_API ~P2P();

    P2P( const P2P& ) = delete;
    P2P& operator=( const P2P& ) = delete;

    // TCP data port announced to other instances. Call before start() (or at any
    // time; the announcement is refreshed). 0 = not announced (peers fall back to the
    // hashed port).
    // EXTENSION: more announced fields (name, capabilities) can be added to the
    // discovery payload here and parsed in P2P::peers().
    CULLib_API void setDataPort( std::uint16_t tcpPort );

    CULLib_API void start();  // begins announcing and listening (background threads)
    CULLib_API void stop();

    // Other instances found so far, excluding this one.
    CULLib_API std::vector<PeerInfo> peers() const;
    CULLib_API bool hasOtherInstances() const
    {
        return !peers().empty();
    }

    CULLib_API const std::string& instanceId() const;

private:
    struct Impl;  // keeps library headers out of this file
    std::unique_ptr<Impl> impl_;
};

}  // namespace Network