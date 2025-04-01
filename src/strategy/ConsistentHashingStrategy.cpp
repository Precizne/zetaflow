#include <iostream>

#include "strategy/ConsistentHashingStrategy.hpp"

namespace ZetaFlow {
namespace Strategy {

ConsistentHashingStrategy::ConsistentHashingStrategy(const std::vector<std::string>& servers) {
    for(const auto& server : servers) {
        size_t hash = hasher(server);
        hash_ring[hash] = server;
    }
}

std::string ConsistentHashingStrategy::getNextServer() {
    std::lock_guard<std::mutex> lock(mtx);

    if(hash_ring.empty()) {
        std::cerr << "[ConsistentHashing] No servers available!" << std::endl;
        return "";
    }

    std::string selected = hash_ring.begin()->second;

    std::cout << "[ConsistentHashing] Selected backend server: " << selected << std::endl;

    return selected;
}

void ConsistentHashingStrategy::updateHealth(const std::string& server, bool is_healthy) {
    std::lock_guard<std::mutex> lock(mtx);
    size_t hash = hasher(server);

    if(!is_healthy) {
        auto it = hash_ring.find(hash);

        if(it != hash_ring.end()) {
            hash_ring.erase(it);

            std::cout << "[ConsistentHashing] Removed unhealthy server: " << server << std::endl;
        }
        else
            std::cout << "[ConsistentHashing] Server " << server << " not found for removal." << std::endl;
    }
    else
        std::cout << "[ConsistentHashing] Health update for server " << server << ": healthy" << std::endl;
}

}
}
