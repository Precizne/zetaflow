#include <iostream>

#include "strategies/LeastConnectionsStrategy.hpp"

LeastConnectionsStrategy::LeastConnectionsStrategy(const std::vector<std::string>& servers) {
    for(const auto& server : servers) {
        server_connections[server] = 0;
    }
}

std::string LeastConnectionsStrategy::getNextServer() {
    std::lock_guard<std::mutex> lock(mtx);

    if(server_connections.empty()) {
        std::cerr << "[LeastConnections] No servers available!" << std::endl;
        return "";
    }

    auto it = std::min_element(server_connections.begin(), server_connections.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    std::cout << "[LeastConnections] Selected backend server: " << it->first << " with " << it->second << " connections." << std::endl;
    return it->first;
}

void LeastConnectionsStrategy::updateHealth(const std::string& server, bool is_healthy) {
    std::lock_guard<std::mutex> lock(mtx);

    if(!is_healthy) {
        auto it = server_connections.find(server);

        if(it != server_connections.end()) {
            server_connections.erase(it);

            std::cout << "[LeastConnections] Removed unhealthy server: " << server << std::endl;
        }
        else
            std::cout << "[LeastConnections] Attempted removal of non-existent server: " << server << std::endl;
    }
    else
        std::cout << "[LeastConnections] Health update for server " << server << ": healthy" << std::endl;
}
