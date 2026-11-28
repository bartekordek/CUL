#include "CUL/Network/CurrentInstance.hpp"
#include "CUL/Network/Peer.hpp"
#include <boost/asio.hpp>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace CUL
{
using boost::asio::ip::tcp;

namespace
{
using Clock = std::chrono::steady_clock;

constexpr auto kLoopSleep = std::chrono::milliseconds( 50 );
constexpr auto kPeerPollInterval = std::chrono::milliseconds( 250 );
constexpr auto kRetryDelay = std::chrono::seconds( 2 );
constexpr auto kReadTimeout = std::chrono::milliseconds( 1000 );

struct PeerState
{
    bool greeted = false;
    Clock::time_point nextAttempt{};
};

// Reads exactly *size* bytes or fails after *timeout* (no blocking forever).
bool readExact( boost::asio::io_context& io,
                tcp::socket& socket,
                std::uint8_t* data,
                std::size_t size,
                std::chrono::milliseconds timeout )
{
    bool done = false;
    boost::system::error_code ec = boost::asio::error::would_block;

    io.restart();
    boost::asio::async_read( socket,
                             boost::asio::buffer( data, size ),
                             [&]( const boost::system::error_code& e, std::size_t )
                             {
                                 ec = e;
                                 done = true;
                             } );
    io.run_for( timeout );
    if( !done )
    {
        boost::system::error_code ignored;
        socket.close( ignored );
        io.restart();
        io.run();  // let the aborted handler finish before locals go away
        return false;
    }
    return !ec;
}

// Reads one frame from a connected socket.
bool readFrame( boost::asio::io_context& io, tcp::socket& socket, Network::Message& out )
{
    std::vector<std::uint8_t> buffer( Network::kHeaderSize );
    if( !readExact( io, socket, buffer.data(), buffer.size(), kReadTimeout ) )
        return false;

    Network::MessageHeader header;
    if( Network::decodeHeader( buffer.data(), buffer.size(), header ) != Network::DecodeStatus::Ok )
        return false;

    buffer.resize( Network::kHeaderSize + header.payloadLen );
    if( header.payloadLen > 0 &&
        !readExact( io, socket, buffer.data() + Network::kHeaderSize, header.payloadLen, kReadTimeout ) )
        return false;

    std::size_t consumed = 0;
    return Network::decode( buffer.data(), buffer.size(), out, consumed ) == Network::DecodeStatus::Ok;
}
}  // namespace

CCurrentInstance::CCurrentInstance() : CCurrentInstance( Callbacks{} )
{
}

CCurrentInstance::CCurrentInstance( Callbacks callbacks )
    : m_callbacks( std::move( callbacks ) ), m_p2p( std::make_unique<Network::P2P>() )
{
    m_mainThread = std::async( std::launch::async, &CCurrentInstance::mainLoop, this );
}

CCurrentInstance::~CCurrentInstance()
{
    stop();
}

const std::string& CCurrentInstance::instanceId() const
{
    return m_p2p->instanceId();
}

std::uint16_t CCurrentInstance::dataPort() const
{
    return m_dataPort;
}

void CCurrentInstance::stop()
{
    m_run = false;
    if( m_mainThread.valid() )
        m_mainThread.wait();
}

void CCurrentInstance::mainLoop()
{
    const auto reportError = [this]( const std::string& text )
    {
        if( m_callbacks.onError )
            m_callbacks.onError( text );
    };

    const std::string& myId = m_p2p->instanceId();

    boost::asio::io_context io;
    tcp::acceptor acceptor( io );
    boost::system::error_code ec;

    const auto tryListen = [&]( std::uint16_t port )
    {
        boost::system::error_code e;
        acceptor.open( tcp::v4(), e );
        if( !e )
            acceptor.bind( tcp::endpoint( tcp::v4(), port ), e );
        if( !e )
            acceptor.listen( boost::asio::socket_base::max_listen_connections, e );
        if( e )
        {
            boost::system::error_code ignored;
            acceptor.close( ignored );
            return false;
        }
        return true;
    };

    // Prefer the hashed port; fall back to an OS-assigned one if it is taken.
    if( !tryListen( dataPortFor( myId ) ) && !tryListen( 0 ) )
    {
        reportError( "Cannot open TCP listener" );
        return;
    }

    // Non-blocking accept so the loop can notice stop() without a pending accept.
    acceptor.non_blocking( true, ec );
    const auto port = acceptor.local_endpoint( ec ).port();
    m_dataPort = port;

    // Announce the real TCP port in the discovery payload.
    m_p2p->setDataPort( port );
    m_p2p->start();

    std::unordered_map<std::string, PeerState> peers;
    auto nextPeerPoll = Clock::now();

    while( m_run )
    {
        bool busy = false;

        // 1) Inbound: one frame per connection.
        {
            tcp::socket inbound( io );
            acceptor.accept( inbound, ec );
            if( !ec )
            {
                busy = true;
                boost::system::error_code remoteEc;
                const auto remote = inbound.remote_endpoint( remoteEc );
                Network::Message message;
                // EXTENSION: loop here (or keep the socket) to support several frames
                // per connection / persistent sessions.
                if( readFrame( io, inbound, message ) )
                    handleMessage( message, remoteEc ? std::string() : remote.address().to_string() );
            }
        }

        // 2) Outbound: greet every newly discovered peer.
        const auto now = Clock::now();
        if( now >= nextPeerPoll )
        {
            nextPeerPoll = now + kPeerPollInterval;

            const auto found = m_p2p->peers();
            std::unordered_set<std::string> present;
            for( const auto& info : found )
            {
                if( !m_run )
                    break;
                present.insert( info.instanceId );

                const auto inserted = peers.try_emplace( info.instanceId );
                PeerState& state = inserted.first->second;
                if( inserted.second && m_callbacks.onPeerDiscovered )
                    m_callbacks.onPeerDiscovered( info );

                if( state.greeted || now < state.nextAttempt )
                    continue;

                const CPeer peer( info.instanceId, info.address, info.port );
                if( peer.sendHello( myId ) )
                {
                    state.greeted = true;
                    if( m_callbacks.onHelloSent )
                        m_callbacks.onHelloSent( info );
                }
                else
                {
                    state.nextAttempt = Clock::now() + kRetryDelay;  // quiet retry later
                }
                busy = true;
            }

            // Forget peers that disappeared so they get greeted again if they return.
            for( auto it = peers.begin(); it != peers.end(); )
                it = present.count( it->first ) ? std::next( it ) : peers.erase( it );
        }

        if( !busy )
            std::this_thread::sleep_for( kLoopSleep );
    }

    m_p2p->stop();
    acceptor.close( ec );
}

void CCurrentInstance::handleMessage( const Network::Message& message, const std::string& remoteAddress )
{
    switch( message.type )
    {
        case Network::MsgType::Hello:
        {
            std::string senderId;
            if( Network::parseHello( message, senderId ) && m_callbacks.onHelloReceived )
                m_callbacks.onHelloReceived( senderId, remoteAddress );
            break;
        }
        // EXTENSION: case Network::MsgType::Ping / Data / ... -> new handlers (and
        // matching callbacks in Callbacks).
        case Network::MsgType::Invalid:
        default:
            break;  // unknown type: ignore (forward compatible)
    }
}
}  // namespace CUL
