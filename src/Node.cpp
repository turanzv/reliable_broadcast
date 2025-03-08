#include "Node.h"
#include "Network.h"
#include <iostream>

Node::Node(uint32_t id, bool is_byzantine, Network& network_reference)
    :id_(id), is_byzantine_(is_byzantine), network_reference_(network_reference) {}

uint32_t Node::get_id() const {
    return id_;
}

bool Node::is_byzantine() const {
    return is_byzantine_;
}

void Node::send_message(uint32_t target_id, const std::string& message) {
    network_reference_.send_message(id_, target_id, message);
}

void Node::receive_message(uint32_t sender_id, const std::string& message) {
    received_messages_.push_back(std::make_pair(sender_id, message));
}

void Node::broadcast_message(const std::string& message) {
    network_reference_.broadcast_message(id_, message);
}

void Node::process_received_messages() {
    for (auto& [sender_id, message] : received_messages_) {
        std::cout << "Node " << id_ << " from " << sender_id << " received message: " << message << std::endl;
    }

    received_messages_.clear();
}

bool Node::has_messages() {
    return !received_messages_.empty();
}