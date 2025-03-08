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
    bool register_node(Node<T>& node);
    bool send_message(uint32_t sender_id, uint32_t target_id, const T& message);
    bool broadcast_message(uint32_t sender_id, const T& message);
    bool deliver_messages();

private:
    std::unordered_map<uint32_t, std::vector<std::pair<uint32_t, T>>> messages_;
    std::unordered_map<uint32_t, Node<T>*> nodes_;
};