#include <iostream>

#include "strategies/LeastConnectionsStrategy.hpp"

LeastConnectionsStrategy::LeastConnectionsStrategy(const std::vector<std::string>& servers) {
    for(const auto& server : servers) {
        server_connections[server] = 0;
    }
}

std::string LeastConnectionsStrategy::getNextServer() {
    std::lock_guard<std::mutex> lock(mtx);
    auto it = std::min_element(server_connections.begin(), server_connections.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    std::cout << "[LeastConnections] Selected backend server: " << it->first << " with " << it->second << " connections." << std::endl;
    return it->first;
}

void LeastConnectionsStrategy::updateHealth(const std::string& server, bool is_healthy) {
    std::lock_guard<std::mutex> lock(mtx);

    if(!is_healthy) {
        server_connections.erase(server);
        std::cout << "[LeastConnections] Removed unhealthy server: " << server << std::endl;
    }
}
