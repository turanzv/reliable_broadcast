#pragma once

#include <cstdint>
#include <string>

struct BroadcastMessage {
    uint32_t sender_id;
    std::string content;
};

class ReliableBroadcast {
public:
    void broadcast(uint32_t sender_id, const BroadcastMessage& message); 
    void receive(uint32_t sender_id, uint32_t recipient_id, const BroadcastMessage& message);
    bool deliver(uint32_t recipient_id);

private:

};