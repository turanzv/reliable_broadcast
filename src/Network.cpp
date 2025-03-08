#include "Network.h"

Network::Network() {
    messages_ = std::unordered_map<uint32_t, std::vector<std::pair<uint32_t, std::string>>>();
    nodes_ = std::unordered_map<uint32_t, Node*>();
}

bool Network::register_node(Node& node) {
    if (nodes_.find(node.get_id()) != nodes_.end()) {
        return false;
    }

    nodes_[node.get_id()] = &node;
    return true;
}

bool Network::send_message(uint32_t sender_id, uint32_t target_id, const std::string& message) {
    if (nodes_.find(target_id) == nodes_.end()) {
        return false;
    }

    messages_[target_id].push_back(std::make_pair(sender_id, message));
    return true;
}

bool Network::broadcast_message(uint32_t sender_id, const std::string& message) {
    if (nodes_.find(sender_id) == nodes_.end()) {
        return false;
    }

    for (auto& [id, node] : nodes_) {
        if (node->get_id() != sender_id) {
            messages_[node->get_id()].push_back(std::make_pair(sender_id, message));
        }
    }

    return true;
}

bool Network::deliver_messages() {
    for (auto& [target_node, message_list] : messages_) {
        for (auto& [sender_id, message] : message_list) {
            nodes_[target_node]->receive_message(sender_id, message);
        }
    }

    messages_.clear();
    return true;
}