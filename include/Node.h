#pragma once

#include <vector>
#include <string>
#include <cstdint>

template <typename T>
class Network;

template <typename T>
class Node {
public:
    Node(uint32_t id, bool is_byzantine, Network<T>& network_reference);

    uint32_t get_id() const;
    bool is_byzantine() const;

    void send_message(uint32_t target_id, const T& message);
    void receive_message(uint32_t sender_id, const T& message);
    void broadcast_message(const T& message);
    void process_received_messages();

    bool has_messages();

private:
    uint32_t id_;
    bool is_byzantine_;
    std::vector<std::pair<uint32_t, T>> received_messages_;
    Network<T>& network_reference_;
};