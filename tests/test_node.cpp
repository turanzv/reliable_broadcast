#include <iostream>
#include <cassert>
#include <string>

#include "Node.h"
#include "Network.h"

void test_node_creation();
void test_node_send_message();
void test_node_broadcast_message();

int main() {
    std::cout << "Running Node test..." << std::endl;

    test_node_creation();
    test_node_send_message();
    test_node_broadcast_message();

    std::cout << "Node test passed!" << std::endl;

    return 0;
}

void test_node_creation() {
    std::cout << "Node creation test..." << std::endl;

    Network<std::string> network;
    Node<std::string> node(1, false, network);

    assert(node.get_id() == 1);
    assert(node.is_byzantine() == false);

    std::cout << "Node creation test complete." << std::endl;
}

void test_node_send_message() {
    std::cout << "Node send message test..." << std::endl;

    Network<std::string> network;
    Node<std::string> node1(1, false, network);
    Node<std::string> node2(2, false, network);

    std::string msg = "Hello Node 2!";
    node1.send_message(2, msg); 

    assert(network.deliver_messages() == true);
    assert(node2.has_messages() == true);

    node2.process_received_messages();
    assert(node2.has_messages() == false);

    std::cout << "Node send message test complete." << std::endl;
}

void test_node_broadcast_message() {
    std::cout << "Node broadcast message test..." << std::endl;

    Network<std::string> network;
    Node<std::string> node1(1, false, network);
    Node<std::string> node2(2, false, network);
    Node<std::string> node3(3, false, network);

    std::string msg = "Hello everyone!";
    node1.broadcast_message(msg);

    assert(network.deliver_messages() == true);
    assert(node2.has_messages() == true);
    assert(node3.has_messages() == true);

    node2.process_received_messages();
    node3.process_received_messages();
    assert(node2.has_messages() == false);
    assert(node3.has_messages() == false);

    std::cout << "Node broadcast message test complete." << std::endl;
}