#include <iostream>
#include "Network.h"
#include "ReliableBroadcast.hpp"

int main() {
    std::cout << "Reliable Broadcast test..." << std::endl;

    Network network = Network<BroadcastMessage<std::string>>();
    ReliableBroadcast<std::string>* rb0 = new ReliableBroadcast<std::string>(4, 1, 0, false, network);
    ReliableBroadcast<std::string>* rb1 = new ReliableBroadcast<std::string>(4, 1, 1, false, network);
    ReliableBroadcast<std::string>* rb2 = new ReliableBroadcast<std::string>(4, 1, 2, false, network);
    ReliableBroadcast<std::string>* rb3 = new ReliableBroadcast<std::string>(4, 1, 3, false, network);

    rb0->broadcast("Hello, World!");

    std::cout << "ROUND 1" << std::endl;
    network.deliver_messages();
    rb1->process_received_messages();
    rb2->process_received_messages();
    rb3->process_received_messages();
    std::cout << "ROUND 2" << std::endl;
    network.deliver_messages(); 
    rb1->process_received_messages();
    rb2->process_received_messages();
    rb3->process_received_messages();
    std::cout << "ROUND 3" << std::endl;
    network.deliver_messages(); 
    rb1->process_received_messages();
    rb2->process_received_messages();
    rb3->process_received_messages();

    return 0;
}