#include "CUL/Network/CurrentInstance.hpp"

#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

// Run two (or more) copies of this example on the same LAN / machine. Each instance
// announces itself via UDP discovery, then sends a binary Hello frame over TCP to
// every peer it finds. Press Enter or Ctrl+C to quit.

namespace
{
std::atomic<bool> g_stop{ false };
std::mutex g_coutMutex;

void onSignal( int )
{
    g_stop = true;
}

void log( const std::string& line )
{
    std::lock_guard<std::mutex> lock( g_coutMutex );
    std::cout << line << std::endl;
}
}  // namespace

int main()
{
    std::signal( SIGINT, onSignal );
    std::signal( SIGTERM, onSignal );

    CUL::CCurrentInstance::Callbacks callbacks;
    callbacks.onPeerDiscovered = []( const Network::PeerInfo& peer )
    {
        log( "[discovered] " + peer.instanceId + " at " + peer.address + ":" +
             std::to_string( peer.port ) );
    };
    callbacks.onHelloSent = []( const Network::PeerInfo& peer )
    {
        log( "[hello sent] -> " + peer.instanceId + " (" + peer.address + ":" +
             std::to_string( peer.port ) + ")" );
    };
    callbacks.onHelloReceived = []( const std::string& id, const std::string& address )
    {
        log( "[hello received] <- " + id + " (from " + address + ")" );
    };
    callbacks.onError = []( const std::string& error )
    {
        log( "[error] " + error );
    };

    CUL::CCurrentInstance instance( callbacks );

    log( "This instance: " + instance.instanceId() );
    log( "Waiting for peers... press Enter or Ctrl+C to quit." );

    // getline blocks, so it lives on its own thread; main just watches the stop flag.
    std::thread(
        []
        {
            std::string line;
            std::getline( std::cin, line );
            g_stop = true;
        } )
        .detach();

    while( !g_stop ) std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

    log( "Shutting down." );
    instance.stop();
    return 0;
}
