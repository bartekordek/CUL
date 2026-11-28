#pragma once

#include "CUL/CUL.hpp"
#include "CUL/GenericUtils/NonCopyable.hpp"
#include "CUL/Network/Message.hpp"
#include <chrono>
#include <cstdint>
#include <string>

namespace CUL
{
// Fallback TCP data port derived from the instance id (20000 + hash % 20000).
// Normally the real port is announced in the discovery payload instead.
CULLib_API std::uint16_t dataPortFor( const std::string& instanceId );

// Outbound connector to one remote instance. Each send opens a short-lived TCP
// connection, writes one frame and closes it.
// EXTENSION: keep the socket open here for persistent / bidirectional sessions.
class CPeer
{
public:
    // inPort == 0 -> dataPortFor( inInstanceId )
    CULLib_API CPeer( const std::string inInstanceId,
                      const std::string inAddr,
                      std::uint16_t inPort = 0 );

    CULLib_API ~CPeer();

    // Connects (with timeout), writes the frame. Returns false on any failure
    // (callers retry later). Blocking, call from a worker thread.
    // EXTENSION: new message types go through this single entry point.
    CULLib_API bool send( const Network::Message& message,
                          std::chrono::milliseconds timeout = std::chrono::milliseconds( 1000 ) ) const;

    CULLib_API bool sendHello( const std::string& ownInstanceId ) const;

    CULLib_API const std::string& instanceId() const
    {
        return m_instanceId;
    }
    CULLib_API const std::string& address() const
    {
        return m_addr;
    }
    CULLib_API std::uint16_t port() const
    {
        return m_port;
    }

    CUL_NONCOPYABLE( CPeer );

private:
    std::string m_instanceId;
    std::string m_addr;
    std::uint16_t m_port;
};
}  // namespace CUL
