#include <iostream>
#include "ReliableBroadcast.h"
#include "Node.h"
#include "Network.h"

template <typename T>
ReliableBroadcast<T>::ReliableBroadcast(uint32_t n, uint32_t f, 
                                        uint32_t node_id, bool is_byzantine, Network<BroadcastMessage<T>> &network_reference)
    : Node<BroadcastMessage<T>>(node_id, is_byzantine, network_reference), n_(n), f_(f) {}

template <typename T>
void ReliableBroadcast<T>::broadcast(const T& message) {
    std::cout << "NODE " << this->id_ << " IS BROADCASTING: " << message << std::endl;
    BroadcastMessage<T> msg = {MessageType::PROPOSE, this->id_, message};
    this->broadcast_message(msg);
}

template <typename T>
void ReliableBroadcast<T>::receive_message(uint32_t sender_id, const BroadcastMessage<T>& message) {
    this->received_messages_.push_back({sender_id, message});
}

template <typename T>
void ReliableBroadcast<T>::process_received_messages() {
    std::vector<std::pair<uint32_t, BroadcastMessage<T>>> to_process = this->received_messages_;
    this->received_messages_.clear();

    for (auto& [sender_id, message] : to_process) {
        std::cout << "NODE " << this->id_ << " RECEIVED MESSAGE: " << message.content << std::endl;
        if (delivered_messages_.find(message.content) != delivered_messages_.end()) {
            return;
        }

        if ( message.type == MessageType::PROPOSE ) {
            std::cout << "NODE " << this->id_ << " RECEIVED PROPOSE: " << message.content << std::endl;
            // not sure if this is necessary if a sender only ever PROPOSEs once
            if ( echo_counts_[message.content].empty() ) {
                BroadcastMessage<T> echo = {MessageType::ECHO, this->id_, message.content};   
                std::cout << "NODE " << this->id_ << " IS ECHOING: " << echo.content << std::endl;
                this->broadcast_message(echo);
                echoed_messages_.insert(message.content);
            }
        } else if ( message.type == MessageType::ECHO ) {
            std::cout << "NODE " << this->id_ << " RECEIVED ECHO: " << message.content << std::endl; 
            echo_counts_[message.content].insert(sender_id);
            uint32_t echo_count = echo_counts_[message.content].size();

            if ( echo_count >= n_ - (2 * f_) && (echoed_messages_.find(message.content) == echoed_messages_.end()) ) {
                BroadcastMessage<T> echo = {MessageType::ECHO, this->id_, message.content};
                std::cout << "NODE " << this->id_ << " IS ECHOING: " << message.content << std::endl;  
                this->broadcast_message(echo);
                echoed_messages_.insert(message.content);
            }

            if ( echo_count >= n_ - f_ - 1 && (delivered_messages_.find(message.content) == delivered_messages_.end()) ) {
                delivered_messages_.insert(message.content);
                std::cout << "NODE " << this->id_ << " DELIVERED MESSAGE: " << message.content << std::endl;
            }
        }
    }
}