#pragma once

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <iostream>

template <typename T>
class Node;

template <typename T>
class Network {
public:
    Network();
    bool register_node(Node<T>* node);
    bool send_message(uint32_t sender_id, uint32_t target_id, const T& message);
    bool broadcast_message(uint32_t sender_id, const T& message);
    bool deliver_messages();

private:
    std::unordered_map<uint32_t, std::vector<std::pair<uint32_t, T>>> messages_;
    std::unordered_map<uint32_t, Node<T>*> nodes_;
};

template <typename T>
Network<T>::Network() {}

template <typename T>
bool Network<T>::register_node(Node<T>* node) {
    std::cout << "Registering Node ID: " << node->get_id() << " of type: " 
              << typeid(*node).name() << std::endl;  // 🔍 Check type

    if (nodes_.find(node->get_id()) != nodes_.end()) {
        return false;
    }

    nodes_[node->get_id()] = node;
    return true;
}

template <typename T>
bool Network<T>::send_message(uint32_t sender_id, uint32_t target_id, const T& message) {
    if (nodes_.find(target_id) == nodes_.end()) {
        return false;
    }

    messages_[target_id].push_back(std::make_pair(sender_id, message));
    return true;
}

template <typename T>
bool Network<T>::broadcast_message(uint32_t sender_id, const T& message) {
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

template <typename T>
bool Network<T>::deliver_messages() {
    for (auto& [target_node, message_list] : messages_) {
        for (auto& [sender_id, message] : message_list) {
            nodes_[target_node]->receive_message(sender_id, message);
        }
    }

    messages_.clear();
    return true;
}