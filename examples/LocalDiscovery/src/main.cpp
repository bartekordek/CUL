#include "CUL/Network/P2P.hpp"

#include <boost/asio.hpp>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

namespace
{
constexpr std::uint16_t kDataPort = 13000;

using boost::asio::ip::tcp;

void runServer( const std::string& myId )
{
    boost::asio::io_context io;
    tcp::acceptor acceptor( io, tcp::endpoint( tcp::v4(), kDataPort ) );
    std::cout << "[server] " << myId << " listening on " << kDataPort << std::endl;

    tcp::socket socket( io );
    acceptor.accept( socket );

    boost::asio::streambuf buffer;
    boost::asio::read_until( socket, buffer, '\n' );
    std::istream input( &buffer );
    std::string line;
    std::getline( input, line );

    std::cout << "[server] received: " << line << std::endl;
}

void runClient( const std::string& myId, const Network::PeerInfo& peer )
{
    boost::asio::io_context io;
    tcp::socket socket( io );

    // Peer may not be listening yet — retry briefly.
    boost::system::error_code ec;
    for( int attempt = 0; attempt < 40; ++attempt )
    {
        socket = tcp::socket( io );
        socket.connect( { boost::asio::ip::make_address( peer.address ), kDataPort }, ec );
        if( !ec )
            break;
        std::this_thread::sleep_for( std::chrono::milliseconds( 250 ) );
    }

    if( ec )
    {
        std::cout << "[client] connect failed: " << ec.message() << std::endl;
        return;
    }

    const std::string msg = "hello from " + myId + "\n";
    boost::asio::write( socket, boost::asio::buffer( msg ) );
    std::cout << "[client] sent to " << peer.instanceId << " @ " << peer.address << ":"
              << kDataPort << std::endl;
}

}  // namespace

int main()
{
    Network::P2P p2p;
    p2p.start();
    std::cout << "I am " << p2p.instanceId() << " (discovery). Waiting for peers..."
              << std::endl;

    Network::PeerInfo peer;
    while( true )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
        if( !p2p.hasOtherInstances() )
            continue;

        peer = p2p.peers().front();
        std::cout << "Found " << peer.instanceId << " at " << peer.address << ":" << peer.port
                  << std::endl;
        break;
    }

    // Lowest instance id becomes the TCP server so two copies on one machine work.
    if( p2p.instanceId() < peer.instanceId )
        runServer( p2p.instanceId() );
    else
        runClient( p2p.instanceId(), peer );

    std::cout << "Done." << std::endl;
    return 0;
}
