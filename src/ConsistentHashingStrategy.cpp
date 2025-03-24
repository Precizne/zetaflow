#include <iostream>

#include "strategies/ConsistentHashingStrategy.hpp"

ConsistentHashingStrategy::ConsistentHashingStrategy(const std::vector<std::string>& servers) {
    for(const auto& server : servers) {
        size_t hash = hasher(server);
        hash_ring[hash] = server;
    }
}

std::string ConsistentHashingStrategy::getNextServer() {
    std::lock_guard<std::mutex> lock(mtx);
    if(hash_ring.empty())
        return "";

    std::string selected = hash_ring.begin()->second;

    std::cout << "[ConsistentHashing] Selected backend server: " << selected << std::endl;
    return selected;
}

void ConsistentHashingStrategy::updateHealth(const std::string& server, bool is_healthy) {
    std::lock_guard<std::mutex> lock(mtx);
    size_t hash = hasher(server);

    if(!is_healthy) {
        hash_ring.erase(hash);
        std::cout << "[ConsistentHashing] Removed unhealthy server: " << server << std::endl;
    }
}
