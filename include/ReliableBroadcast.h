#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Network.h"

enum class MessageType {
    PROPOSE,
    ECHO
};

template <typename T>
struct BroadcastMessage {
    MessageType type;
    uint32_t sender_id;
    T content;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const BroadcastMessage<T>& msg) {
    os << "[";
    if (msg.type == MessageType::PROPOSE) os << "PROPOSE";
    else if (msg.type == MessageType::ECHO) os << "ECHO";
    else os << "UNKNOWN";
    os << "] From: " << msg.sender_id << " Content: " << msg.content;
    return os;
}

template <typename T>
class ReliableBroadcast : public Node<BroadcastMessage<T>> {
public:
    ReliableBroadcast(uint32_t n, uint32_t f, uint32_t node_id, bool is_byzantine, Network<BroadcastMessage<T>>& network_reference);
    ~ReliableBroadcast() = default;

    void broadcast(const T& message); 
    void receive_message(uint32_t sender_id, const BroadcastMessage<T>& message) override;
    void process_received_messages() override;

private:
    std::unordered_map<T, std::unordered_set<uint32_t>> echo_counts_;
    std::unordered_set<T> echoed_messages_;
    std::unordered_set<T> delivered_messages_;
    uint32_t n_, f_;
};