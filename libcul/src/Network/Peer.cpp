#include "CUL/Network/Peer.hpp"

#include <boost/asio.hpp>

namespace CUL
{
using boost::asio::ip::tcp;

CPeer::CPeer( const std::string inInstanceId, const std::string inAddr, std::uint16_t inPort )
    : m_instanceId( inInstanceId ),
      m_addr( inAddr ),
      m_port( inPort != 0 ? inPort : dataPortFor( inInstanceId ) )
{
}

CPeer::~CPeer() = default;

bool CPeer::send( const Network::Message& message, std::chrono::milliseconds timeout ) const
{
    const auto frame = Network::encode( message );
    if( frame.empty() )
        return false;

    boost::system::error_code ec;
    const auto address = boost::asio::ip::make_address( m_addr, ec );
    if( ec )
        return false;

    boost::asio::io_context io;
    tcp::socket socket( io );

    // Async connect + run_for gives us a connect timeout with a plain io_context.
    bool connected = false;
    boost::system::error_code connectEc = boost::asio::error::would_block;
    socket.async_connect( tcp::endpoint( address, m_port ),
                          [&]( const boost::system::error_code& e )
                          {
                              connectEc = e;
                              connected = true;
                          } );
    io.run_for( timeout );
    if( !connected || connectEc )
    {
        socket.close( ec );
        return false;
    }

    // Frames are tiny; the blocking write completes immediately into the socket buffer.
    boost::asio::write( socket, boost::asio::buffer( frame ), ec );
    if( ec )
        return false;

    socket.shutdown( tcp::socket::shutdown_send, ec );
    return true;
}

bool CPeer::sendHello( const std::string& ownInstanceId ) const
{
    return send( Network::makeHello( ownInstanceId ) );
}

std::uint16_t dataPortFor( const std::string& instanceId )
{
    std::uint32_t h = 2166136261u;
    for( unsigned char c : instanceId )
        h = ( h ^ c ) * 16777619u;
    return static_cast<std::uint16_t>( 20000u + ( h % 20000u ) );
}
}  // namespace CUL
