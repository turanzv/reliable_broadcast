#pragma once

#include <vector>
#include <map>
#include <string>
#include <cstdint>
#include <iostream>
#include "Node.h"

class Network {
public:
    Network();
    bool register_node(Node& node);
    bool send_message(uint32_t sender_id, uint32_t target_id, const std::string& message);
    bool broadcast_message(uint32_t sender_id, const std::string& message);
    bool deliver_messages();

private:
    std::unordered_map<uint32_t, std::vector<std::pair<uint32_t, std::string>>> messages_;
    std::unordered_map<uint32_t, Node*> nodes_;
};