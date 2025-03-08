#include "Node.h"
#include "Network.h"
#include <iostream>

template <typename T>
Node<T>::Node(uint32_t id, bool is_byzantine, Network<T>& network_reference)
    :id_(id), is_byzantine_(is_byzantine), network_reference_(network_reference) {}

template <typename T>
uint32_t Node<T>::get_id() const {
    return id_;
}

template <typename T>
bool Node<T>::is_byzantine() const {
    return is_byzantine_;
}

template <typename T>
void Node<T>::send_message(uint32_t target_id, const T& message) {
    network_reference_.send_message(id_, target_id, message);
}

template <typename T>
void Node<T>::receive_message(uint32_t sender_id, const T& message) {
    received_messages_.push_back(std::make_pair(sender_id, message));
}

template <typename T>
void Node<T>::broadcast_message(const T& message) {
    network_reference_.broadcast_message(id_, message);
}

template <typename T>
void Node<T>::process_received_messages() {
    for (auto& [sender_id, message] : received_messages_) {
        std::cout << "Node " << id_ << " from " << sender_id << " received message: " << message << std::endl;
    }

    received_messages_.clear();
}

template <typename T>
bool Node<T>::has_messages() {
    return !received_messages_.empty();
}