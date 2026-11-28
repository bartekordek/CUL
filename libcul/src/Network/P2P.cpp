#include "CUL/Network/P2P.hpp"

#include "CUL/Network/Peer.hpp"

#include <cstdio>
#include <cstdlib>
#include <list>
#include <random>

#include "udp_discovery_peer.hpp"

namespace Network
{

namespace
{

// Discovery payload: "inst:<id>;tcp:<port>"  (";tcp:<port>" optional)
// EXTENSION: append further ";key:value" fields for new announced properties.
const std::string kIdPrefix = "inst:";
const std::string kTcpTag = ";tcp:";

std::string makeInstanceId()
{
    std::random_device rd;
    std::uint64_t v = ( std::uint64_t( rd() ) << 32 ) | rd();
    char buf[17];
    std::snprintf( buf, sizeof( buf ), "%016llx", static_cast<unsigned long long>( v ) );
    return buf;
}

// NOTE: check the byte order the library uses for ip(); swap if the output looks
// reversed.
std::string ipToString( std::uint32_t ip )
{
    char buf[16];
    std::snprintf( buf,
                   sizeof( buf ),
                   "%u.%u.%u.%u",
                   ( ip >> 24 ) & 0xFF,
                   ( ip >> 16 ) & 0xFF,
                   ( ip >> 8 ) & 0xFF,
                   ip & 0xFF );
    return buf;
}

}  // namespace

struct P2P::Impl
{
    std::uint16_t port;
    std::uint32_t appId;
    std::string id = makeInstanceId();
    std::uint16_t dataPort = 0;
    bool running = false;
    udpdiscovery::Peer peer;

    std::string userData() const
    {
        std::string s = kIdPrefix + id;
        if( dataPort != 0 )
            s += kTcpTag + std::to_string( dataPort );
        return s;
    }
};

P2P::P2P( std::uint16_t port, std::uint32_t appId ) : impl_( new Impl )
{
    impl_->port = port;
    impl_->appId = appId;
}

P2P::~P2P()
{
    stop();
}

void P2P::start()
{
    if( impl_->running )
        return;

    udpdiscovery::PeerParameters params;
    params.set_port( impl_->port );
    params.set_application_id( impl_->appId );
    params.set_can_discover( true );
    params.set_can_be_discovered( true );
    params.set_send_timeout_ms( 1000 );  // announce every second (library default: 5s)
    params.set_discovered_peer_ttl_ms( 5000 );

    // On failure the library reports on stderr and we stay "not running".
    impl_->running = impl_->peer.Start( params, impl_->userData() );
}

void P2P::setDataPort( std::uint16_t tcpPort )
{
    impl_->dataPort = tcpPort;
    if( impl_->running )
        impl_->peer.SetUserData( impl_->userData() );
}

void P2P::stop()
{
    if( !impl_ || !impl_->running )
        return;
    impl_->peer.StopAndWaitForThreads();
    impl_->running = false;
}

std::vector<PeerInfo> P2P::peers() const
{
    std::vector<PeerInfo> out;
    if( !impl_->running )
        return out;

    std::list<udpdiscovery::DiscoveredPeer> found = impl_->peer.ListDiscovered();
    for( const auto& d : found )
    {
        const std::string& data = d.user_data();
        if( data.compare( 0, kIdPrefix.size(), kIdPrefix ) != 0 )
            continue;

        std::string id = data.substr( kIdPrefix.size() );
        std::uint16_t tcpPort = 0;
        const auto tagPos = id.find( kTcpTag );
        if( tagPos != std::string::npos )
        {
            const std::string portStr = id.substr( tagPos + kTcpTag.size() );
            id.resize( tagPos );
            const unsigned long parsed = std::strtoul( portStr.c_str(), nullptr, 10 );
            if( parsed > 0 && parsed <= 65535 )
                tcpPort = static_cast<std::uint16_t>( parsed );
        }

        if( id.empty() || id == impl_->id )
            continue;  // malformed, or that's us

        PeerInfo info;
        info.instanceId = id;
        info.address = ipToString( d.ip_port().ip() );
        info.port = tcpPort != 0 ? tcpPort : CUL::dataPortFor( id );
        out.push_back( std::move( info ) );
    }
    return out;
}

const std::string& P2P::instanceId() const
{
    return impl_->id;
}

}  // namespace Network