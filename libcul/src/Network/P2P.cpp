#include "CUL/Network/P2P.hpp"

#include <cstdio>
#include <list>
#include <random>

#include "udp_discovery_peer.hpp"

namespace Network
{

namespace
{

const std::string kIdPrefix = "inst:";

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
    bool running = false;
    udpdiscovery::Peer peer;
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

    impl_->peer.Start( params, kIdPrefix + impl_->id );
    impl_->running = true;
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
        if( id == impl_->id )
            continue;  // that's us

        PeerInfo info;
        info.instanceId = id;
        info.address = ipToString( d.ip_port().ip() );
        info.port = d.ip_port().port();
        out.push_back( std::move( info ) );
    }
    return out;
}

const std::string& P2P::instanceId() const
{
    return impl_->id;
}

}  // namespace Network