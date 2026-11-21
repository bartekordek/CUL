#include "CUL/Network/P2P.hpp"

#include <chrono>
#include <iostream>
#include <thread>

int main()
{
    Network::P2P p2p;
    p2p.start();
    std::cout << "I am " << p2p.instanceId() << "\n";

    // Announcements are periodic, so give discovery a few seconds.
    for( int i = 0; i < 10; ++i )
    {
        std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );
        if( p2p.hasOtherInstances() )
            break;
    }

    auto peers = p2p.peers();
    if( peers.empty() )
    {
        std::cout << "No other instances found.\n";
    }
    else
    {
        for( auto& p : peers )
            std::cout << "Found " << p.instanceId << " at " << p.address << ":" << p.port
                      << "\n";
    }
}