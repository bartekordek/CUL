#pragma once

#include "CUL/GenericUtils/NonCopyable.hpp"
#include "CUL/CUL.hpp"
#include "CUL/Network/Message.hpp"
#include "CUL/Network/P2P.hpp"
#include <atomic>
#include <cstdint>
#include <functional>
#include <future>
#include <memory>
#include <string>

namespace CUL
{
// Local P2P node: announces itself over UDP discovery, listens for inbound TCP
// frames, and sends a binary Hello to every newly discovered peer.
class CCurrentInstance
{
public:
    // All callbacks are invoked from the instance's worker thread; keep them short
    // and thread-safe. Any of them may be left empty.
    // EXTENSION: add callbacks (onMessage, onPeerLost, ...) here.
    struct Callbacks
    {
        std::function<void( const Network::PeerInfo& )> onPeerDiscovered;
        std::function<void( const Network::PeerInfo& )> onHelloSent;
        // (sender instance id, remote ip address)
        std::function<void( const std::string&, const std::string& )> onHelloReceived;
        std::function<void( const std::string& )> onError;
    };

    CULLib_API CCurrentInstance();
    CULLib_API explicit CCurrentInstance( Callbacks callbacks );

    CULLib_API ~CCurrentInstance();
    CUL_NONCOPYABLE( CCurrentInstance );

    CULLib_API const std::string& instanceId() const;
    // TCP data port we listen on; 0 until the listener is up.
    CULLib_API std::uint16_t dataPort() const;

    CULLib_API void stop();

protected:
private:
    void mainLoop();
    // EXTENSION: dispatch point for every received frame; add new MsgType handlers.
    void handleMessage( const Network::Message& message, const std::string& remoteAddress );

    Callbacks m_callbacks;
    std::unique_ptr<Network::P2P> m_p2p;
    std::future<void> m_mainThread;
    std::atomic<bool> m_run{ true };
    std::atomic<std::uint16_t> m_dataPort{ 0 };
};
}  // namespace CUL
